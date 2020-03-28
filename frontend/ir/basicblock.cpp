#include <ir/basicblock.hpp>
#include <spdlog/fmt/fmt.h>

BasicBlock::BasicBlock(uint label, std::string name, SymbolTable* scope)
{
    this->scope = scope;
    this->label = label;
    this->name = name;
}

std::string BasicBlock::toString() const
{
    std::string string;
    std::string padding((this->scope->depth - 1) * 3, ' ');
    string += padding + fmt::format("BB [{}] ({})\n", this->name, this->scope->name);
    for (const Statement& stmt : statements) {
        string += padding + " │" + stmt.toString() + "\n";
    }
    string += padding + " └────────────────────\n";
    return string;
}
