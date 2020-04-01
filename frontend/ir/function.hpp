#pragma once

#include <symboltable.hpp>
#include <ast.hpp>
#include <ir/basicblock.hpp>

class Function
{
private:
    std::vector<BasicBlock> constructWhile(const AST* ast);
    std::vector<BasicBlock> constructFor(const AST* ast);
    std::vector<BasicBlock> constructIf(const AST* ast);
    std::vector<BasicBlock> populateBB(const AST* ast);
    uint nextBlockID = 0;
public:
    std::string name;
    std::vector<BasicBlock> blocks;
    SymbolTable* scope;

    Function(const AST* funcNode);
    std::string toString() const;
};