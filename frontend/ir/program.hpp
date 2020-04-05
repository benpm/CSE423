/**
 * @file program.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for Program data structure
 * @date 2020-03-11
 *
 */
#pragma once

#include <utility>
#include <vector>
#include <ast.hpp>
#include <ir/function.hpp>

/**
 * @brief Data structure for an IR program
 * @details Is composed of a series of functions
 *
 */
class Program
{
public:
    std::vector<std::pair<std::string, Function>> functions;

    Program(const AST& ast);
    Program(std::string filename);
    std::string outputToString();
    void outputToFile(std::string filename);
    void print();
};
