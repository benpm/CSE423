#pragma once

#include <ir/program.hpp>

class Optimizer
{
private:
    Arg evaluate(const Statement& statement);
    bool canEvaluate(const Statement& statement);
    bool foldConstants(BasicBlock& block);
public:
    void optimize(Program& program);
};