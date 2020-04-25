#include <codeGeneration/CodeGenerator.hpp>

CodeGenerator::CodeGenerator(const Program& program)
{
    // do the thing
}

Instruction::Instruction(OpCode opCode, const std::vector<std::string> args)
{
    this->opCode = opCode;
    this->args = args;
}