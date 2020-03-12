#pragma once

#include <basicblock.hpp>

class Function
{
public:
    std::string name;
    std::vector<BasicBlock> basicBlocks;

    Function(std::string name);
};