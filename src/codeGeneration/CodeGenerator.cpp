#include <codeGeneration/CodeGenerator.hpp>
#include <codeGeneration/MemoryAllocator.hpp>
#include <map>
#include <unordered_set>
#include <iostream>

CodeGenerator::CodeGenerator(const Program& program, bool printDebug)
{
    this->printDebug = printDebug;

    // Insert globals into data section (from a block of assignments, ass for short)
    for (const Statement& ass : program.globals.statements) {
        const std::string name = ass.args.at(0).val.sval;
        const Arg& value = ass.args.at(1);
        this->insert({fmt::format(".globl {}", name)});
        this->insert({".data"});
        this->insert({fmt::format(".align 8", name)});
        this->insert({fmt::format(".type {}, @object", name)});
        this->insert({fmt::format(".size {}, 8", name)});
        this->insert({fmt::format("{}: .quad {}", name, value.toString())});
    }

    // Generate code for functions
    for (const auto& pair : program.functions) {
        this->insert({".text"});
        this->insert({fmt::format(".globl {}", pair.first)});
        this->insert({fmt::format(".type {}, @function", pair.first)});
        this->genFunction(program, pair.second);
    }
}

void CodeGenerator::genFunction(const Program& program, const Function& func)
{
    this->curFuncName = func.name;
    MemoryAllocator allocator(*this);
    allocator.stackSize = WORD_SIZE;

    // Insert globals (from a block of assignments, ass for short)
    for (const Statement& ass : program.globals.statements) {
        allocator.storageMap.emplace(ass.args.at(0), InstrArg{
            Register::rip,
            std::string(ass.args.at(0).val.sval)
        });
    }

    // Indicate function
    this->insert({fmt::format("# FUNCTION {}", func.name)});

    // Populate memory allocator map with stack locations of parameters
    int n = 2;
    for (const Arg& param : func.parameters) {
        allocator.parameter(param, n);
        n += 1;
    }

    // Function label, create frame
    this->insert({fmt::format("{}:", func.name)});
    this->insert({OpCode::PUSH, {Register::rbp}});
    this->insert({OpCode::MOV, {Register::rsp, Register::rbp}});

    for (const BasicBlock& block : func.blocks) {
        // Jump label for this basic block
        this->insert({fmt::format(".{}.{}:", this->curFuncName, block.label)});
        for (const Statement& stmt : block.statements) {
            this->insert({fmt::format("# {}", stmt.toString())});
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
    
    Instruction sumInstr{OpCode::ADD, {opA, opB}};  // add %opA, %opB
    Instruction movInstr{OpCode::MOV, {opB, dest}}; // mov %opB, %dest

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
    
    Instruction mulInstr{OpCode::IMUL, {opA, opB}}; // imul %opA, %opB
    Instruction movInstr{OpCode::MOV,  {opB, dest}}; // mov %opB, %dest

    this->insert(mulInstr);
    this->insert(movInstr);

    allocator.save(stmt.args.at(0));

    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genDIV(MemoryAllocator& allocator, const Statement& stmt)
{
    // Evict whatever was in %eax previously, saving it if needed, moving dividend in
    allocator.insertAt(stmt.args.at(1), Register::rax);
    // Evict whatever was in %edx previously, saving it if needed, moving result (remainder) in
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // Divisor is argument for idiv
    InstrArg arg = allocator.getReg(stmt.args.at(2));
    // Clear %edx
    allocator.evict(Register::rdx);
    // Division instruction (%eax(arg1)/arg(arg2))
    Instruction idivInstr{OpCode::IDIV, {arg}}; // idiv %arg
    // Move instruction
    Instruction movInstr{OpCode::MOV, {{Register::rax}, result}, "save quotient"};

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
    Instruction subInstr{OpCode::SUB, {arg2, arg1}}; // sub %arg2, %arg1
    Instruction movInstr{OpCode::MOV, {arg1, dest}}; // mov %arg1, %dest

    this->insert(subInstr);
    this->insert(movInstr);

    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1), stmt.args.at(2)});

}

void CodeGenerator::genMOD(MemoryAllocator& allocator, const Statement& stmt)
{
    // Evict whatever was in %eax previously, saving it if needed, moving dividend in
    allocator.insertAt(stmt.args.at(1), Register::rax);
    // Evict whatever was in %edx previously, saving it if needed, moving result (remainder) in
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // Divisor is argument for idiv
    InstrArg arg = allocator.getReg(stmt.args.at(2));
    // Clear %edx
    allocator.evict(Register::rdx);
    // Division instruction (%eax(arg1)/arg(arg2))
    Instruction idivInstr{OpCode::IDIV, {arg}}; // idiv %arg
    // Move instruction
    Instruction movInstr{OpCode::MOV, {{Register::rdx}, result}, "save remainder"};

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
    
    Instruction negInstr{OpCode::NEG, {op}}; // neg %op
    Instruction movInstr{OpCode::MOV, {op, dest}}; // mov %op, %dest

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

    Instruction movInstr{OpCode::MOV, {src, dest}};

    this->insert(movInstr);
    allocator.save(stmt.args.at(0));
    allocator.deregister({stmt.args.at(0), stmt.args.at(1)});
}

void CodeGenerator::genJUMP(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    Instruction jmp{OpCode::JMP, {label}};
    this->insert(jmp);
}

void CodeGenerator::genJUMP_LT(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmplt{OpCode::JL, {label}};   // jl label       | if opA - opB < 0
    
    this->insert(cmp);
    this->insert(jmplt);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_GT(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpge{OpCode::JG, {label}};   // jg label       | if opA - opB > 0
    
    this->insert(cmp);
    this->insert(jmpge);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_LE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmple{OpCode::JLE, {label}};  // jle label      | if opA - opB <= 0
    
    this->insert(cmp);
    this->insert(jmple);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_GE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpge{OpCode::JGE, {label}};  // jge label      | if opA - opB >= 0
    
    this->insert(cmp);
    this->insert(jmpge);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_EQ(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpneq{OpCode::JE, {label}};  // jle label      | if opA - opB == 0
    
    this->insert(cmp);
    this->insert(jmpneq);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_NEQ(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpneq{OpCode::JNE, {label}}; // jle label      | if opA - opB != 0
    
    this->insert(cmp);
    this->insert(jmpneq);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_IF_TRUE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpnz{OpCode::JNZ, {label}};  // jnz label      | if opA - opB != 0
    
    this->insert(cmp);
    this->insert(jmpnz);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genJUMP_IF_FALSE(MemoryAllocator& allocator, const Statement& stmt)
{
    std::string label = fmt::format(".{}.{}", this->curFuncName, stmt.args.at(0).val.label);
    InstrArg opA = allocator.getReg(stmt.args.at(1));
    InstrArg opB = allocator.getReg(stmt.args.at(2));
    
    Instruction cmp{OpCode::CMP, {opB, opA}}; // cmp %opB, $opA | opA - opB
    Instruction jmpnz{OpCode::JZ, {label}};   // jz label       | if opA - opB == 0
    
    this->insert(cmp);
    this->insert(jmpnz);

    allocator.deregister({stmt.args.at(1), stmt.args.at(2)});
}

void CodeGenerator::genRETURN(MemoryAllocator& allocator, const Statement& stmt)
{
    // Place return arg into %eax
    allocator.insertAt(stmt.args.at(0), Register::rax);
    // Restore old call frame
    this->insert({fmt::format("# stack size is {}", allocator.stackSize)});
    // Move the stack pointer back to the base pointer
    this->insert({OpCode::MOV, {Register::rbp, Register::rdx}});
    this->insert({OpCode::SUB, {Register::rsp, Register::rdx}});
    this->insert({OpCode::ADD, {Register::rdx, Register::rsp}});
    this->insert({OpCode::POP, {Register::rbp}});
    // Add return instruction
    Instruction ret{OpCode::RET, {}};
    this->insert(ret);
    allocator.deregister(stmt.args.at(0));
}

void CodeGenerator::genCALL(MemoryAllocator& allocator, const Statement& stmt)
{
    // Push all arguments onto the stack (in reverse order!)
    int argsSize = 0;
    for (auto it = stmt.args.rbegin(); it < stmt.args.rend() - 2; it++) {
        this->insert({OpCode::PUSH, {allocator.get(*it)}});
        argsSize += WORD_SIZE;
    }
    // Clear all registers (including %eax)
    allocator.clear();
    // Get a register for return value
    InstrArg result = allocator.getReg(stmt.args.at(0));
    // Insert call instruction (function label / name is second argument of CALL statement)
    Instruction callInstr{OpCode::CALL, {std::string(stmt.args.at(1).val.sval)}};
    this->insert(callInstr);
    // Remove call arguments from frame
    if (argsSize > 0) {
        Instruction addInstr{OpCode::ADD, {argsSize, Register::rsp}};
        this->insert(addInstr);
    }
    // Save out result
    // Instruction movInstr{OpCode::MOV, {{Register::eax}, result}, "save result"};
    allocator.save(stmt.args.at(0));
    allocator.deregister(stmt.args.at(0));
}

void CodeGenerator::genNO_OP(MemoryAllocator& allocator, const Statement& stmt)
{

}

void CodeGenerator::insert(const Instruction& instr)
{
    this->instrs.push_back(instr);
    if (this->printDebug) {
        fmt::print(instr.toString() + "\n");
    }
}

void CodeGenerator::print()
{
    for (const Instruction& instr : this->instrs)
    {
        fmt::print("{}\n", instr.toString());
    }
}
