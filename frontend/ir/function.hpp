#pragma once

#include <symboltable.hpp>
#include <ast.hpp>
#include <ir/basicblock.hpp>

class Function
{
public:
    std::string name;
    std::vector<BasicBlock*> basicBlocks;
    SymbolTable* scope;

    Function(const AST* funcNode);
    std::string toString() const;
};