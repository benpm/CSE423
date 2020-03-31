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
    int lineNum = -1;

    BasicBlock(int lineNum, uint label, std::string name, SymbolTable* scope);
    std::string toString() const;
};