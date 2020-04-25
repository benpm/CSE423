#include <cassert>
#include <codeGeneration/MemoryAllocator.hpp>


MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen), regOccupied(4) // Number of open registers
{
}

InstrArg MemoryAllocator::getReg(const Arg& arg)
{
    // Check if argument is already in a register, return the register if it is
    if (this->regMap.count(arg)) {
        return InstrArg{this->regMap[arg]};
    }

    // It is not in a register so we must check if it's on the stack
    // If it is, move it in to register openReg and return
    // If its not on the stack, just return a register for it
    Register openReg = this->getNextAvailReg(arg);
    if (this->stackOffsetMap.count(arg)) {
        int offset = this->stackOffsetMap[arg];

        InstrArg src{Register::EBP, offset}; // offset(%ebp)
        InstrArg dest{openReg};              // %reg
        Instruction loadInstr(Instruction::MOV, {src, dest}); // mov offset(%ebp) %reg

        this->codeGen.instrs.push_back(loadInstr);
        this->regMap.emplace(arg, openReg);
    }

    return openReg;
}

Register MemoryAllocator::getNextAvailReg(const Arg& arg)
{
    // Find next unoccupied register. THIS CURRENTLY DOES NOT
    // TAKE INTO ACCOUNT FLOATS!!!!
    for (int i = 0; i < this->regOccupied.size(); i++) {
        if (!this->regOccupied.at(i)) {
            this->regOccupied.at(i) = true;
            return (Register)i;
        }
    }
    throw fmt::format("Holy shit we ran out of registers on {}", arg.toString());
}

void MemoryAllocator::save(const Arg& arg)
{
    assert(arg.type == Arg::Type::NAME);
    if (this->regMap.count(arg)) {
        Register reg = this->regMap.at(arg);
        if (this->stackOffsetMap.count(arg)) {
            // If already on the stack, save to that location
            int offset = this->stackOffsetMap.at(arg);
            // Move from register to location on stack
            InstrArg src{reg}; // %reg
            InstrArg dest{Register::EBP, offset}; // offset(%ebp)
            Instruction instr(Instruction::MOV, {src, dest}); // mov %reg, offset(%ebp)
            codeGen.instrs.push_back(instr);
        } else {
            // Push onto stack, mapping where on stack we are
            this->stackOffsetMap.emplace(arg, -this->stackSize);
            InstrArg arg{reg}; // %reg
            Instruction instr(Instruction::PUSH, {arg}); // push %reg
            this->codeGen.instrs.push_back(instr);
            // Increase stack size member
            this->stackSize += 4;
        }
    } else {
        throw fmt::format("Cannot save {}, arg not assigned a register", arg.toString());
    }
}

void MemoryAllocator::deregister(const Arg& arg)
{   
    // Arg must be in register to deregister it. If its not we throw an exception
    if (this->regMap.count(arg)) {
        Register reg = this->regMap[reg];
        this->regMap.erase(arg);
        this->regOccupied.at(reg) = false;
        return;
    }

    throw fmt::format("Deregistering a register that is not allocated! {}", arg.toString());
}
