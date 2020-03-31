#pragma once

#include <symboltable.hpp>
#include <ast.hpp>
#include <ir/basicblock.hpp>

class Function
{
private:
    uint constructWhile(const AST* ast, uint tempn);
    uint constructFor(const AST* ast, uint tempn);
    uint constructIf(const AST* ast, uint tempn);
    uint populateBB(const AST* ast, uint tempn);
public:
    std::string name;
    std::vector<BasicBlock*> blocks;
    SymbolTable* scope;

    Function(const AST* funcNode);
    std::string toString() const;
};