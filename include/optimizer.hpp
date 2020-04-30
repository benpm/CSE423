#pragma once

#include <ir/program.hpp>

class Optimizer
{
private:
    Arg evaluate(const Statement& statement);
    bool canEvaluate(const Statement& statement);
    bool foldConstants(BasicBlock& block);
    void propagate(
        bool& proceed,
        std::vector<std::pair<BasicBlock&, Statement&>>& stmts,
        std::set<size_t>& jumpBlocks,
        bool onlyRemoveTemps=false);
public:
    void optimize(Program& program);
    void optimize(BasicBlock& block);
};