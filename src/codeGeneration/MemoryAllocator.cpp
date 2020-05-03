#include <cassert>
#include <codeGeneration/MemoryAllocator.hpp>
#include <spdlog/spdlog.h>
#include <magic_enum.hpp>

/**
 * @brief Tracks memory/register location of variables
 * 
 * @param codeGen Code generator object so we can insert instructions
 */
MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen)
{
    this->regOccupied = std::vector<bool>(USABLE_REGS, false);
    this->regLRU = std::vector<size_t>(USABLE_REGS, 0);
    this->stackSize = 0;
}

/**
 * @brief Returns the location of an argument (register, stack, etc)
 * 
 * @param arg Relevant arg
 * @return InstrArg 
 */
InstrArg MemoryAllocator::getLoc(const Arg& arg)
{
    spdlog::debug("--> Getting location for {}", arg.toString());
    
    if (this->regMap.count(arg)) { // Argument is already in a register, return reg
        return this->getReg(arg);
    } else if (this->storageMap.count(arg)) { // If on stack, return offset(%ebp)
        return this->storageMap.at(arg);
    } if (arg.type != Arg::NAME) {  // If immediate return that immediate
        return arg;
    }

    // Not found, error
    spdlog::error("MemoryAllocator::get -> {} not found!", arg.toString());
    exit(EXIT_FAILURE);
}

/**
 * @brief Returns the register an argument is in
 * 
 * @param arg Relevant arg
 * @return InstrArg 
 */
InstrArg MemoryAllocator::getReg(const Arg& arg)
{
    assert(this->regMap.count(arg));

    InstrArg instrArg = this->regMap.at(arg);
    this->step += 1;
    this->regLRU.at(std::get<Register>(instrArg.arg)) = this->step;
    return instrArg;
}

/**
 * @brief Allocates space ON THE STACK
 * 
 * @param arg Relevant arg
 */
void MemoryAllocator::allocateArg(const Arg& arg)
{
    if ((this->storageMap.count(arg) == 0) && (arg.type == Arg::NAME)) {
        Instruction instr{OpCode::PUSH, {0}, fmt::format("{} at -{}(%rbp)", arg.toString(), stackSize)}; // push $0

        this->storageMap.emplace(arg, InstrArg{Register::rbp, -this->stackSize});
        this->stackSize += WORD_SIZE; // Increase stack size member

        this->codeGen.insert(instr);
        spdlog::debug("----> Pushing {} to -{}(%ebp)", arg.toString(), this->stackSize);
    }
}

/**
 * @brief Allocates a register for a given arg
 * 
 * @param arg Relevant arg
 * @return InstrArg 
 */
InstrArg MemoryAllocator::allocateReg(const Arg& arg)
{
    spdlog::debug("--> Getting register for {}", arg.toString());
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        spdlog::debug("----> already in {}", this->getReg(arg).toString());
        return InstrArg{this->getReg(arg)};
    }

    // It is not in a register so we must check if it's on the stack
    // If it is, move it in to register openReg and return
    // If its not on the stack, just return a register for it
    InstrArg dest{this->getNextAvailReg(arg)};
    InstrArg src = this->getLoc(arg);
    Instruction loadInstr{OpCode::MOV, {src, dest}};

    this->codeGen.insert(loadInstr);
    this->regMap.emplace(arg, dest);

    return dest;
}

/**
 * @brief Returns a register for an argument and evicts a register if necessary
 * 
 * @param arg Relevant arg
 * @return Register 
 */
Register MemoryAllocator::getNextAvailReg(const Arg& arg)
{
    // Find next unoccupied register. THIS CURRENTLY DOES NOT
    // TAKE INTO ACCOUNT FLOATS!!!!
    for (int i = 0; i < this->regOccupied.size(); i++) {
        if (!this->regOccupied.at(i)) {
            spdlog::debug("----> Putting {} in {}", arg.toString(), magic_enum::enum_name((Register) i));
            this->regOccupied.at(i) = true;
            return (Register)i;
        }
    }

    // Prefer to evict registers with immediates assigned
    for (auto pair : this->regMap) {
        if (pair.first.type != Arg::NAME) {
            spdlog::debug("----> Choosing to evict {} from {}", pair.first.toString(), pair.second.toString());
            Register reg = std::get<Register>(pair.second.arg);
            this->evict(reg);
            this->regOccupied.at(reg) = true;
            this->regMap.emplace(arg, InstrArg{reg});
            return reg;
        }
    }

    // Find and evict least recently used register
    Register reg = (Register)(std::min_element(this->regLRU.begin(), this->regLRU.end()) - this->regLRU.begin());
    this->evict(reg);
    this->regOccupied.at(reg) = true;
    this->regMap.emplace(arg, InstrArg{reg});
    return reg;
}

/**
 * @brief Transfers location of A to location of B WITHOUT inserting instructions
 *        (assume B's location was destroyed, does not save)
 * 
 * @param argA 
 * @param argB 
 */
void MemoryAllocator::transfer(const Arg& argA, const Arg& argB)
{
    assert(this->regMap.count(argB));

    // Deregister argA if in register
    if (this->regMap.count(argA)) {
        this->deregister(argA);
    }
    // Grab B's register location, then deregister it
    InstrArg loc = this->getReg(argB);
    Register reg = std::get<Register>(loc.arg);
    this->deregister(argB);
    // Set argA to be in argB's location
    this->regOccupied.at(reg) = true;
    this->regMap.emplace(argA, reg);
}

/**
 * @brief Saves an argument to its permanent storage location
 * 
 * @param arg Relevant argument
 */
void MemoryAllocator::save(const Arg& arg)
{
    spdlog::debug("--> Saving {}", arg.toString());

    if (this->regMap.count(arg) == 0) {
        spdlog::error("Cannot save {}, arg not assigned a register", arg.toString());
        exit(EXIT_FAILURE);
    }
    if (this->storageMap.count(arg) == 0) {
        spdlog::error("Cannot save {}, arg not a non-register location!", arg.toString());
        exit(EXIT_FAILURE);
    }
    assert(arg.type == Arg::Type::NAME);

    InstrArg src{this->getReg(arg)};
    InstrArg dest = this->storageMap.at(arg);
    Instruction instr = {OpCode::MOV, {src, dest}}; // mov %reg, offset(%ebp)
    this->codeGen.insert(instr);

    spdlog::debug("----> Restoring {} to {}", arg.toString(), dest.toString());
}

/**
 * @brief Overload that allows you to deregister multiple args at once
 * 
 * @param args Relevant args
 */
void MemoryAllocator::deregister(const std::unordered_set<Arg, ArgHash> args)
{
    for (const Arg& arg : args) {
        this->deregister(arg);
    }
}

/**
 * @brief Deregisters a single arg (does not save to permanent storage, only marks the register it's in as unused)
 * 
 * @param arg Relevant arg
 */
void MemoryAllocator::deregister(const Arg& arg)
{
    spdlog::debug("--> Deregistering {}", arg.toString());
    // Arg must be in register to deregister it. If its not we error
    if (this->regMap.count(arg)) {
        Register reg = std::get<Register>(this->getReg(arg).arg);
        this->regMap.erase(arg);
        this->regOccupied.at(reg) = false;
        return;
    }

    spdlog::error("Deregistering a register that is not allocated! {}", arg.toString());
}

/**
 * @brief Evicts an argument from the given register
 * 
 * @param reg Relevant register
 */
void MemoryAllocator::evict(Register reg)
{
    // Try to deallocate the occupied register
    for (auto& pair : this->regMap) {
        if (std::get<Register>(pair.second.arg) == reg) {
            spdlog::debug("----> {} occupied, saving it out.", magic_enum::enum_name(reg));
            if (pair.first.type == Arg::NAME) {
                this->save(pair.first);
            }
            this->deregister(pair.first);
            break;
        }
    }
}


/**
 * @brief Inserts an argument at the given register
 * 
 * @param arg Argument to insert
 * @param reg Insertion location
 */
void MemoryAllocator::insertAt(const Arg& arg, Register reg)
{
    spdlog::debug("--> Inserting {} in {}", arg.toString(), magic_enum::enum_name(reg));

    this->evict(reg);

    InstrArg dest{reg};
    InstrArg src = this->getLoc(arg);
    if (std::holds_alternative<Register>(src.arg)) { // In a register
        this->save(arg);
        this->deregister(arg);
    }

    spdlog::debug("----> {} In {}, moving to {}", arg.toString(), src.toString(), magic_enum::enum_name(reg));

    Instruction mov{OpCode::MOV, {src, dest}};
    this->regMap.emplace(arg, dest);
    this->regOccupied.at(reg) = true;
    this->codeGen.insert(mov);
}

/**
 * @brief Dumps all registers to permanent storage
 * 
 */
void MemoryAllocator::clear()
{
    for (int i = 0; i < regOccupied.size(); i++) {
        if (regOccupied.at(i)) {
            this->evict((Register)i);
        }
    }
}

/**
 * @brief Registers a function parameter on the stack
 * 
 * @param arg Funciton parameter
 * @param n nth parameter
 */
void MemoryAllocator::parameter(const Arg& arg, int n)
{
    this->storageMap.emplace(arg, InstrArg{Register::rbp, n * 8});
    codeGen.insert({fmt::format("# param {} at {}(%rbp)", arg.toString(), n * 8)});
}