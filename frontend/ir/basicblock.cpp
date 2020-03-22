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
    string += fmt::format("BLOCK [{}]\n", this->name);
    for (const Statement& stmt : statements) {
        string += "  " + stmt.toString() + "\n";
    }
    return string;
}
