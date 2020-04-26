#pragma once

#include <ir/program.hpp>
#include <codeGeneration/Instruction.hpp>

class MemoryAllocator;

class CodeGenerator
{
private:
    void genFunction(const Function& func);
    void genStatement(MemoryAllocator& allocator, const Statement& stmt);
    void genADD(MemoryAllocator& allocator, const Statement& stmt);

public:
    std::vector<Instruction> instrs;
    CodeGenerator(const Program& program);

    void printInstructs();
};