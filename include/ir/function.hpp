/**
 * @file function.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for Function data structure
 * @date 2020-03-11
 *
 */
#pragma once

#include <fstream>
#include <set>
#include <symboltable.hpp>
#include <ast.hpp>
#include <ir/basicblock.hpp>

/**
 * @brief Data structure for an IR function
 * @details Is composed of a series of basic blocks
 *
 */
class Function
{
private:
    std::vector<BasicBlock> constructWhile(const AST* ast);
    std::vector<BasicBlock> constructFor(const AST* ast);
    std::vector<BasicBlock> constructIf(const AST* ast);
    BasicBlock createComparisonBlock(const AST* node, uint jumpto);
    std::vector<BasicBlock> constructCond(const AST* ast, uint success, uint failure);
    void assignCondLabels(std::vector<BasicBlock>& blocks, uint success, uint failure);
    std::vector<BasicBlock> populateBB(const AST* ast);
    bool combineBlocks();
    bool isJumpDestination(const BasicBlock& block) const;
    uint nextBlockID = 0;
    std::map<uint, std::string> gotoBlockLocs;
    std::map<std::string, uint> labelBlockLocs;
public:
    std::string name;
    std::vector<BasicBlock> blocks;
    std::vector<Arg> parameters;
    SymbolTable* scope;

    Function(const AST* funcNode);
    Function(std::string name, std::ifstream& csv, std::vector<Arg> parameters);
    std::string toString() const;
    std::string toCSV() const;
};
