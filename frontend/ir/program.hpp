#pragma once

#include <unordered_map>
#include <ast.hpp>
#include <ir/function.hpp>

// Intermediate representation program
class Program
{
public:
    std::unordered_map<std::string, Function> functions;

    Program(const AST& ast, const SymbolTable& symTable);
    Program(std::string irCode);
    std::string outputToString();
    void print();
};