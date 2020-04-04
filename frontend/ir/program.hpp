#pragma once

#include <utility>
#include <vector>
#include <ast.hpp>
#include <ir/function.hpp>

// Intermediate representation program
class Program
{
public:
    std::vector<std::pair<std::string, Function>> functions;

    Program(const AST& ast);
    Program(std::string irCode);
    std::string outputToString();
    void outputToFile(std::string filename);
    void print();
};