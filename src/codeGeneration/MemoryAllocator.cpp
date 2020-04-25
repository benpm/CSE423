#include <cassert>
#include <codeGeneration/MemoryAllocator.hpp>


MemoryAllocator::MemoryAllocator(CodeGenerator& codeGen) :
    codeGen(codeGen)
{

}


std::string MemoryAllocator::getReg(const Arg& arg)
{
    // Check if argument is already in a register
    if (this->regMap.count(arg)) {
        Register reg = this->regMap[arg];
        return this->enumToString.at(reg);
    }

    // It is not in a register so we must check if it's on the stack
    // If it is, move it in to register Reg and return
    // If its not on the stack, just return a register for it
    Register reg = this->getNextAvailReg(arg);
    if (this->stackOffsetMap.count(arg)) {
        int offset = this->stackOffsetMap[arg];
        std::string src = fmt::format("{}(%ebp)");
        std::string dest = this->enumToString.at(reg);

        Instruction loadInstr(Instruction::MOV, {src, dest});
        this->codeGen.instrs.push_back(loadInstr);
        this->regMap.emplace(arg, reg);
    }

    return this->enumToString.at(reg);
}

MemoryAllocator::Register MemoryAllocator::getNextAvailReg(const Arg& arg)
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
            int loc = this->stackOffsetMap.at(arg);
            // Move from register to location on stack
            Instruction instr(Instruction::MOV, {
                this->enumToString.at(reg),
                fmt::format("{}(%rbp)", loc)
            });
            codeGen.instrs.push_back(instr);
        } else {
            // Push onto stack, mapping where on stack we are
            this->stackOffsetMap.emplace(arg, -this->stackSize);
            Instruction instr(Instruction::PUSH, {
                this->enumToString.at(reg)
            });
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
