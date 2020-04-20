/**
 * @file basicblock.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for BasicBlock data structure
 * @date 2020-03-11
 *
 */
#pragma once

#include <symboltable.hpp>
#include <ir/statement.hpp>

/**
 * @brief Data structure for an IR basic block
 * @details A basic block has no control flow within it
 *
 */
class BasicBlock
{
private:
    static uint nextTemp;
public:
    uint label;
    std::string name;
    std::vector<Statement> statements;
    int lineNum = -1;

    BasicBlock(int lineNum, uint label, std::string name);
    BasicBlock(uint label, std::string name, std::ifstream& csv);
    std::string toString() const;
    std::string toCSV() const;
    Arg expand(const AST* ast, bool start=true);
};
