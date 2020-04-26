#include <cassert>
#include <codeGeneration/MemoryAllocator.hpp>
#include <spdlog/spdlog.h>
#include <magic_enum.hpp>


MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen), regOccupied(4) // Number of open registers
{
}

InstrArg MemoryAllocator::getReg(const Arg& arg)
{
    spdlog::debug("--> Getting register for {}", arg.toString());
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        spdlog::debug("----> already in {}", magic_enum::enum_name(this->regMap[arg]));
        return InstrArg{this->regMap[arg]};
    }

    // It is not in a register so we must check if it's on the stack
    // If it is, move it in to register openReg and return
    // If its not on the stack, just return a register for it
    Register openReg = this->getNextAvailReg(arg);
    if (this->stackOffsetMap.count(arg)) {
        int offset = this->stackOffsetMap[arg];

        InstrArg src{Register::ebp, offset}; // offset(%ebp)
        InstrArg dest{openReg};              // %reg
        Instruction loadInstr(Instruction::MOV, {src, dest}); // mov offset(%ebp) %reg

        this->codeGen.insert(loadInstr);
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
            codeGen.insert(instr);
        } else {
            // Push onto stack, mapping where on stack we are
            this->stackOffsetMap.emplace(arg, -this->stackSize);
            InstrArg arg{reg}; // %reg
            Instruction instr(Instruction::PUSH, {arg}); // push %reg
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
    spdlog::debug("--> Deregistering {}, Cur size {}", arg.toString(), this->regMap.size());
    // Arg must be in register to deregister it. If its not we error
    if (this->regMap.count(arg)) {
        Register reg = this->regMap.at(arg);
        this->regMap.erase(arg);
        this->regOccupied.at(reg) = false;
        spdlog::debug("----> new size {}", this->regMap.size());
        return;
    }

    spdlog::error("Deregistering a register that is not allocated! {}", arg.toString());
}
