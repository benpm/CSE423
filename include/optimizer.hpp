#pragma once

#include <ir/program.hpp>

class Optimizer
{
private:
    Arg evaluate(const Statement& statement);
    bool optimizeBlock(BasicBlock& block);
    bool canEvaluate(const Statement& statement);
public:
    void optimize(Program& program);
};