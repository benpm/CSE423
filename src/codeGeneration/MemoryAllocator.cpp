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

InstrArg MemoryAllocator::get(const Arg& arg)
{
    spdlog::debug("--> Getting location for {}", arg.toString());
    
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        return InstrArg{this->regMap.at(arg)};
    }

    // If on stack, return offset(%ebp)
    if (this->stackOffsetMap.count(arg)) {
        return InstrArg{Register::ebp, this->stackOffsetMap.at(arg)};
    }

    // If immediate return that immediate
    if (arg.type != Arg::NAME) {
        return InstrArg{arg};
    }

    // Not found, error
    spdlog::error("MemoryAllocator::get -> {} not found!", arg.toString());
    exit(EXIT_FAILURE);
}

InstrArg MemoryAllocator::getReg(const Arg& arg)
{
    spdlog::debug("--> Getting register for {}", arg.toString());
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        spdlog::debug("----> already in {}", magic_enum::enum_name(this->regMap.at(arg)));
        return InstrArg{this->regMap.at(arg)};
    }

    // It is not in a register so we must check if it's on the stack
    // If it is, move it in to register openReg and return
    // If its not on the stack, just return a register for it
    Register openReg = this->getNextAvailReg(arg);
    if (this->stackOffsetMap.count(arg)) {
        int offset = this->stackOffsetMap.at(arg);

        InstrArg src{Register::ebp, offset}; // offset(%ebp)
        InstrArg dest{openReg};              // %reg
        Instruction loadInstr(Instruction::MOV, {src, dest}); // mov offset(%ebp) %reg

        this->codeGen.insert(loadInstr);
    }

    // If immediate, move the immediate into the register
    if (arg.type != Arg::NAME) {
        Instruction movInstr(Instruction::MOV, {arg, openReg});
        this->codeGen.insert(movInstr);
    }

    this->regMap.emplace(arg, openReg);
    return openReg;
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
    
    assert(arg.type == Arg::Type::NAME);
    if (this->regMap.count(arg)) {
        Register reg = this->regMap.at(arg);
        if (this->stackOffsetMap.count(arg)) {
            // If already on the stack, save to that location
            int offset = this->stackOffsetMap.at(arg);
            // Move from register to location on stack
            InstrArg src{reg}; // %reg
            InstrArg dest{Register::ebp, offset}; // offset(%ebp)
            Instruction instr(Instruction::MOV, {src, dest}); // mov %reg, offset(%ebp)
            spdlog::debug("----> Restoring {} to {}", arg.toString(), dest.toString());
            codeGen.insert(instr);
        } else {
            // Push onto stack, mapping where on stack we are
            this->stackOffsetMap.emplace(arg, -this->stackSize);
            InstrArg regArg{reg}; // %reg
            Instruction instr(Instruction::PUSH, {regArg}); // push %reg
            spdlog::debug("----> Pushing {} to -{}(%ebp)", arg.toString(), this->stackSize);

            this->codeGen.insert(instr);
            // Increase stack size member
            this->stackSize += 4;
        }
    } else {
        spdlog::error("Cannot save {}, arg not assigned a register", arg.toString());
    }
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
        Register reg = this->regMap.at(arg);
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
        if (pair.second == reg) {
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

    if (this->regMap.count(arg)) {
        InstrArg src{this->regMap.at(arg)};
        InstrArg dest{reg};

        this->save(arg);
        this->deregister(arg);

        Instruction mov{Instruction::MOV, {src, dest}};
        spdlog::debug("----> {} In {}, moving to {}", arg.toString(), src.toString(), magic_enum::enum_name(reg));

        this->regMap.emplace(arg, reg);
        this->regOccupied.at(reg) = true;

        this->codeGen.insert(mov);
        return;
    }

    // Arg is an immediate, mov straight into the register
    if (arg.type != Arg::NAME) {
        InstrArg src{arg};
        InstrArg dest{reg};

        Instruction mov{Instruction::MOV, {src, dest}};
        spdlog::debug("----> {} In {}, moving to {}", arg.toString(), src.toString(), magic_enum::enum_name(reg));

        this->regMap.emplace(arg, reg);
        this->regOccupied.at(reg) = true;

        this->codeGen.insert(mov);
        return;
    }

    // It is not in a register so we must check if it's on the stack
    if (this->stackOffsetMap.count(arg)) {
        int offset = this->stackOffsetMap.at(arg);

        InstrArg src{Register::ebp, offset}; // offset(%ebp)
        InstrArg dest{reg};                  // %reg
        Instruction loadInstr(Instruction::MOV, {src, dest}); // mov offset(%ebp) %reg

        spdlog::debug("----> {} at {}, moving to {}", arg.toString(), src.toString(), magic_enum::enum_name(reg));

        this->regMap.emplace(arg, reg);
        this->regOccupied.at(reg) = true;
        this->codeGen.insert(loadInstr);
        return;
    }

    spdlog::error("Inserting an argument {} at {} that doesnt exist yet!", arg.toString(), magic_enum::enum_name(reg));
    exit(EXIT_FAILURE);
}
