#pragma once

#include <symboltable.hpp>
#include <ir/statement.hpp>

class BasicBlock
{
public:
    uint label;
    std::string name;
    SymbolTable* scope;
    std::vector<Statement> statements;

    BasicBlock(uint label, std::string name, SymbolTable* scope);
};