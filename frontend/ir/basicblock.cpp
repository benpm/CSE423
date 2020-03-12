#include <ir/basicblock.hpp>

BasicBlock::BasicBlock(uint label, std::string name, SymbolTable* scope)
{
    this->scope = scope;
    this->label = label;
    this->name = name;
}
