#include <codeGeneration/CodeGenerator.hpp>
#include <codeGeneration/MemoryAllocator.hpp>
#include <map>
#include <unordered_set>
#include <iostream>

CodeGenerator::CodeGenerator(const Program& program)
{
    // <-- Insert program header stuff HERE
    for (const auto& pair : program.functions) {
        this->genFunction(pair.second);
    }
}

void CodeGenerator::genFunction(const Function& func)
{
    MemoryAllocator allocator(*this);

    // <-- Insert function header stuff HERE
    this->insert({fmt::format("{}:", func.name)});
    for (const BasicBlock& block : func.blocks) {
        // <-- Insert label
        this->insert({fmt::format("BB{}:", block.label)});
        for (const Statement& stmt : block.statements) {
            this->insert({fmt::format("; {}", stmt.toString())});
            this->genStatement(allocator, stmt);
        }
    }
}

void CodeGenerator::genStatement(MemoryAllocator& allocator, const Statement& stmt)
{
    switch(stmt.type) {
        case Statement::ADD:           this->genADD(allocator, stmt);           break;
        case Statement::MUL:           this->genMUL(allocator, stmt);           break;
        case Statement::DIV:           this->genDIV(allocator, stmt);           break;
        case Statement::SUB:           this->genSUB(allocator, stmt);           break;
        case Statement::MOD:           this->genMOD(allocator, stmt);           break;
        case Statement::MINUS:         this->genMINUS(allocator, stmt);         break;
        case Statement::ASSIGN:        this->genASSIGN(allocator, stmt);        break;
        case Statement::JUMP:          this->genJUMP(allocator, stmt);          break;
        case Statement::JUMP_LT:       this->genJUMP_LT(allocator, stmt);       break;
        case Statement::JUMP_GT:       this->genJUMP_GT(allocator, stmt);       break;
        case Statement::JUMP_LE:       this->genJUMP_LE(allocator, stmt);       break;
        case Statement::JUMP_GE:       this->genJUMP_GE(allocator, stmt);       break;
        case Statement::JUMP_EQ:       this->genJUMP_EQ(allocator, stmt);       break;
        case Statement::JUMP_NEQ:      this->genJUMP_NEQ(allocator, stmt);      break;
        case Statement::JUMP_IF_TRUE:  this->genJUMP_IF_TRUE(allocator, stmt);  break;
        case Statement::JUMP_IF_FALSE: this->genJUMP_IF_FALSE(allocator, stmt); break;
        case Statement::RETURN:        this->genRETURN(allocator, stmt);        break;
        case Statement::CALL:          this->genCALL(allocator, stmt);          break;
        case Statement::NO_OP:         this->genNO_OP(allocator, stmt);         break;
        default: spdlog::error("Unhandled statement type"); exit(EXIT_FAILURE); break;
    }
}

void CodeGenerator::genADD(MemoryAllocator& allocator, const Statement& stmt)
{
    // dest = opA + opB
    InstrArg dest = allocator.getReg(stmt.args.at(0));
    InstrArg opA  = allocator.getReg(stmt.args.at(1));
    InstrArg opB  = allocator.getReg(stmt.args.at(2));
    
    Instruction sumInstr{Instruction::ADD, {opA, opB}};  // add %opA, %opB
    Instruction movInstr{Instruction::MOV, {opB, dest}}; // mov %opB, %dest

    this->insert(sumInstr);
    this->insert(movInstr);

    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genMUL(MemoryAllocator& allocator, const Statement& stmt)
{
    // dest = opA * opB
    InstrArg dest = allocator.getReg(stmt.args.at(0));
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction mulInstr{Instruction::IMUL, {opA, opB}}; // imul %opA, %opB
    Instruction movInstr{Instruction::MOV,  {opB, dest}}; // mov %opB, %dest

    this->insert(mulInstr);
    this->insert(movInstr);

    allocator.save(stmt.args.at(0));

    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genDIV(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genSUB(MemoryAllocator& allocator, const Statement& stmt)
{
    // dest = arg1 - arg2
    InstrArg dest = allocator.getReg(stmt.args.at(0));
    InstrArg arg1 = allocator.getReg(stmt.args.at(1));
    InstrArg arg2 = allocator.getReg(stmt.args.at(2));
    
    // Note that this is backwards, arg1 = arg1 - arg2, not arg2 = arg1 - arg2
    Instruction subInstr{Instruction::SUB, {arg2, arg1}}; // sub %arg2, %arg1
    Instruction movInstr{Instruction::MOV, {arg1, dest}}; // mov %arg1, %dest

    this->insert(subInstr);
    this->insert(movInstr);

    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});

}

void CodeGenerator::genMOD(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genMINUS(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genASSIGN(MemoryAllocator& allocator, const Statement& stmt)
{
    // dest = src
    InstrArg dest = allocator.getReg(stmt.args.at(0));
    InstrArg src  = allocator.getReg(stmt.args.at(1));

    Instruction movInstr{Instruction::MOV, {src, dest}};

    this->insert(movInstr);
    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1)});
}

void CodeGenerator::genJUMP(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    Instruction jmp{Instruction::JMP, {label}};
    this->insert(jmp);
}

void CodeGenerator::genJUMP_LT(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_GT(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_LE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmple{Instruction::JLE, {label}};  // jle label      | if opA - opB <= 0
    
    this->insert(cmp);
    this->insert(jmple);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_GE(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_EQ(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_NEQ(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_IF_TRUE(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genJUMP_IF_FALSE(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genRETURN(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genCALL(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::genNO_OP(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::insert(const Instruction& instr)
{
    this->instrs.push_back(instr);
    std::cout << instr.toString() << std::endl;
}

void CodeGenerator::printInstructs()
{
    for (const Instruction& instr : this->instrs)
    {
        fmt::print("{}\n", instr.toString());
    }
}
