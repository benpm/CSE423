#pragma once

#include <ir/program.hpp>
#include <codeGeneration/Instruction.hpp>

class MemoryAllocator;

class CodeGenerator
{
private:
    std::string curFuncName;
    bool printDebug;

    void genFunction(const Program& program, const Function& func);
    void genStatement(MemoryAllocator& allocator, const Statement& stmt);
    void genADD(MemoryAllocator& allocator, const Statement& stmt);
    void genMUL(MemoryAllocator& allocator, const Statement& stmt);
    void genDIV(MemoryAllocator& allocator, const Statement& stmt);
    void genSUB(MemoryAllocator& allocator, const Statement& stmt);
    void genMOD(MemoryAllocator& allocator, const Statement& stmt);
    void genMINUS(MemoryAllocator& allocator, const Statement& stmt);
    void genASSIGN(MemoryAllocator& allocator, const Statement& stmt);
    void genJUMP(MemoryAllocator& allocator, const Statement& stmt);
    void genConditionalJump(MemoryAllocator& allocator, const Statement& stmt);
    void genRETURN(MemoryAllocator& allocator, const Statement& stmt);
    void genCALL(MemoryAllocator& allocator, const Statement& stmt);
    void genPRINTF(MemoryAllocator& allocator, const Statement& stmt);
    void optimizeAssembly();
    
public:
    std::vector<Instruction> instrs;
    CodeGenerator(const Program& program, bool printDebug);

    void insert(const Instruction& instr);

    void print();
};