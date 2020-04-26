#include <codeGeneration/CodeGenerator.hpp>
#include <codeGeneration/MemoryAllocator.hpp>
#include <map>

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
    this->instrs.push_back({fmt::format("{}:", func.name)});
    for (const BasicBlock& block : func.blocks) {
        // <-- Insert label
        this->instrs.push_back({fmt::format("BB{}:", block.label)});
        for (const Statement& stmt : block.statements) {
            this->instrs.push_back({fmt::format("; {}", stmt.toString())});
            this->genStatement(allocator, stmt);
        }
    }
}

void CodeGenerator::genStatement(MemoryAllocator& allocator, const Statement& stmt)
{
    switch(stmt.type) {
        case Statement::ADD: this->genADD(allocator, stmt); break;
        default: /* throw "Unhandled statement type"; */ break;
    }
}

void CodeGenerator::genADD(MemoryAllocator& allocator, const Statement& stmt)
{
    this->instrs.push_back({
        Instruction::ADD,
        {{Register::eax},
         {Register::eax}}
    });
}

void CodeGenerator::printInstructs()
{
    for (const Instruction& instr : this->instrs)
    {
        fmt::print("{}\n", instr.toString());
    }
}
