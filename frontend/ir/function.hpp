#pragma once

#include <ir/basicblock.hpp>

class Function
{
public:
    std::string name;
    std::vector<BasicBlock> basicBlocks;

    Function(std::string name);
};