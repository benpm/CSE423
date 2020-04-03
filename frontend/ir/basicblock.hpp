#pragma once

#include <symboltable.hpp>
#include <ir/statement.hpp>

class BasicBlock
{
private:
    static uint nextTemp;
public:
    uint label;
    std::string name;
    SymbolTable* scope;
    std::vector<Statement> statements;
    int lineNum = -1;

    BasicBlock(int lineNum, uint label, std::string name, SymbolTable* scope);
    std::string toString() const;
    Arg expand(const AST* ast);
};