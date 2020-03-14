#pragma once

#include <ast.hpp>
#include <ir/basicblock.hpp>

class Function
{
public:
    std::string name;
    std::vector<BasicBlock> basicBlocks;

    Function(const AST& funcNode);
};