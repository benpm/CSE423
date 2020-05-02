#include <cassert>
#include <codeGeneration/MemoryAllocator.hpp>
#include <spdlog/spdlog.h>
#include <magic_enum.hpp>


MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen)
{
    this->regOccupied = std::vector<bool>(USABLE_REGS, false);
    this->stackSize = 0;
}

InstrArg MemoryAllocator::getLoc(const Arg& arg)
{
    spdlog::debug("--> Getting location for {}", arg.toString());
    
    if (this->regMap.count(arg)) { // Argument is already in a register, return reg
        return this->regMap.at(arg);
    } else if (this->storageMap.count(arg)) { // If on stack, return offset(%ebp)
        return this->storageMap.at(arg);
    } if (arg.type != Arg::NAME) {  // If immediate return that immediate
        return arg;
    }

    // Not found, error
    spdlog::error("MemoryAllocator::get -> {} not found!", arg.toString());
    exit(EXIT_FAILURE);
}

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


InstrArg MemoryAllocator::allocateReg(const Arg& arg)
{
    spdlog::debug("--> Getting register for {}", arg.toString());
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        spdlog::debug("----> already in {}", this->regMap.at(arg).toString());
        return InstrArg{this->regMap.at(arg)};
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
    spdlog::error("Holy shit we ran out of registers on {}", arg.toString());
    return Register::no_reg;
}

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

    InstrArg src{this->regMap.at(arg)};
    InstrArg dest = this->storageMap.at(arg);
    Instruction instr = {OpCode::MOV, {src, dest}}; // mov %reg, offset(%ebp)
    this->codeGen.insert(instr);

    spdlog::debug("----> Restoring {} to {}", arg.toString(), dest.toString());
}

void MemoryAllocator::deregister(const std::unordered_set<Arg, ArgHash> args)
{
    for (const Arg& arg : args) {
        this->deregister(arg);
    }
}

void MemoryAllocator::deregister(const Arg& arg)
{
    spdlog::debug("--> Deregistering {}", arg.toString());
    // Arg must be in register to deregister it. If its not we error
    if (this->regMap.count(arg)) {
        Register reg = std::get<Register>(this->regMap.at(arg).arg);
        this->regMap.erase(arg);
        this->regOccupied.at(reg) = false;
        return;
    }

    spdlog::error("Deregistering a register that is not allocated! {}", arg.toString());
}

void MemoryAllocator::evict(Register reg)
{
    // Try to deallocate the occupied register
    for (auto& pair : this->regMap) {
        if (std::get<Register>(pair.second.arg) == reg) {
            spdlog::debug("----> {} occupied, saving it out.", magic_enum::enum_name(reg));
            this->save(pair.first);
            this->deregister(pair.first);
            break;
        }
    }
}

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

void MemoryAllocator::clear()
{
    for (int i = 0; i < regOccupied.size(); i++) {
        if (regOccupied.at(i)) {
            this->evict((Register)i);
        }
    }
}

void MemoryAllocator::parameter(const Arg& arg, int n)
{
    this->storageMap.emplace(arg, InstrArg{Register::rbp, n * 8});
    codeGen.insert({fmt::format("# param {} at {}(%rbp)", arg.toString(), n * 8)});
}