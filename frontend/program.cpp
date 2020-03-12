#include <iostream>
#include <program.hpp>

Program::Program(const AST& ast, const SymbolTable& symTable)
{
    // Build IR program from ast and symbol table
}

Program::Program(std::string irCode)
{
    // Build IR program from plaintext IR code
}

std::string Program::outputToString()
{
    // Create plaintext representation of this IR program
    return std::string();
}

void Program::print()
{
    std::cout << outputToString() << std::endl;
}