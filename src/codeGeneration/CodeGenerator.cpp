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

    // Function label as well as saving / creating call frame
    this->insert({fmt::format("; FUNCTION {}", func.name)});
    this->insert({fmt::format("{}:", func.name)});
    this->insert({Instruction::PUSH, {Register::ebp}});
    this->insert({Instruction::MOV, {Register::ebp, Register::esp}});
    for (const BasicBlock& block : func.blocks) {
        // Jump label for this basic block
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
    // Evict whatever was in %eax previously, saving it if needed, moving dividend in
    allocator.insertAt(stmt.args.at(1), Register::eax);
    // Evict whatever was in %edx previously, saving it if needed, moving result (remainder) in
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // Divisor is argument for idiv
    InstrArg arg = allocator.getReg(stmt.args.at(2));
    // Clear %edx
    allocator.evict(Register::edx);
    // Division instruction (%eax(arg1)/arg(arg2))
    Instruction idivInstr{Instruction::IDIV, {arg}}; // idiv %arg
    // Move instruction
    Instruction movInstr{Instruction::MOV, {{Register::eax}, result}, "save quotient"};

    this->insert(idivInstr);
    this->insert(movInstr);
    // This will save the quotient, stored in %eax, to result loc
    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});
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
    // Evict whatever was in %eax previously, saving it if needed, moving dividend in
    allocator.insertAt(stmt.args.at(1), Register::eax);
    // Evict whatever was in %edx previously, saving it if needed, moving result (remainder) in
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // Divisor is argument for idiv
    InstrArg arg = allocator.getReg(stmt.args.at(2));
    // Clear %edx
    allocator.evict(Register::edx);
    // Division instruction (%eax(arg1)/arg(arg2))
    Instruction idivInstr{Instruction::IDIV, {arg}}; // idiv %arg
    // Move instruction
    Instruction movInstr{Instruction::MOV, {{Register::edx}, result}, "save remainder"};

    this->insert(idivInstr);
    this->insert(movInstr);
    // This will save the remainder, stored in %edx, to result loc
    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genMINUS(MemoryAllocator& allocator, const Statement& stmt)
{
    // dest = -op
    InstrArg dest = allocator.getReg(stmt.args.at(0));
    InstrArg op = allocator.getReg(stmt.args.at(1));
    
    Instruction negInstr{Instruction::NEG, {op}}; // neg %op
    Instruction movInstr{Instruction::MOV, {op, dest}}; // mov %op, %dest

    this->insert(negInstr);
    this->insert(movInstr);
    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1)});
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
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmplt{Instruction::JL, {label}};   // jl label       | if opA - opB < 0
    
    this->insert(cmp);
    this->insert(jmplt);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_GT(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpge{Instruction::JG, {label}};   // jg label       | if opA - opB > 0
    
    this->insert(cmp);
    this->insert(jmpge);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
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
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpge{Instruction::JGE, {label}};  // jge label      | if opA - opB >= 0
    
    this->insert(cmp);
    this->insert(jmpge);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_EQ(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpneq{Instruction::JE, {label}};  // jle label      | if opA - opB == 0
    
    this->insert(cmp);
    this->insert(jmpneq);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_NEQ(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpneq{Instruction::JNE, {label}}; // jle label      | if opA - opB != 0
    
    this->insert(cmp);
    this->insert(jmpneq);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_IF_TRUE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpnz{Instruction::JNZ, {label}};  // jnz label      | if opA - opB != 0
    
    this->insert(cmp);
    this->insert(jmpnz);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_IF_FALSE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format("BB{}", stmt.args.at(0).val.ival);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{Instruction::CMP, {opA, opB}}; // cmp %opA, $opB | opA - opB
    Instruction jmpnz{Instruction::JZ, {label}};   // jz label       | if opA - opB == 0
    
    this->insert(cmp);
    this->insert(jmpnz);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genRETURN(MemoryAllocator& allocator, const Statement& stmt)
{
    // Restore old call frame
    Instruction mov{Instruction::MOV, {Register::esp, Register::ebp}};
    Instruction pop{Instruction::POP, {Register::ebp}};
    this->insert(mov);
    this->insert(pop);
    // Place return arg into %eax, add return instruction
    allocator.insertAt(stmt.args.at(0), Register::eax);
    Instruction ret{Instruction::RET, {}};
    this->insert(ret);
    allocator.deregister(stmt.args.at(0));
}

void CodeGenerator::genCALL(MemoryAllocator& allocator, const Statement& stmt)
{
    // Push all arguments onto the stack (in reverse order!)
    int argsSize = 0;
    for (auto it = stmt.args.rbegin(); it < stmt.args.rend() - 2; it++) {
        this->insert({Instruction::PUSH, {allocator.get(*it)}});
        argsSize += 4;
    }
    // Clear %eax
    allocator.evict(Register::eax);
    // Get a register for return value
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // TODO: Clear other registers
    // Insert call instruction (function label / name is second argument of CALL statement)
    Instruction callInstr{Instruction::CALL, {std::string(stmt.args.at(1).val.sval)}};
    this->insert(callInstr);
    // Remove call arguments from frame
    if (argsSize > 0) {
        Instruction addInstr{Instruction::ADD, {argsSize, Register::esp}};
        this->insert(addInstr);
    }
    // Save out result
    // Instruction movInstr{Instruction::MOV, {{Register::eax}, result}, "save result"};
    allocator.save(stmt.args.at(0));
    allocator.deregister(stmt.args.at(0));
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
