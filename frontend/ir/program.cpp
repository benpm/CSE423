#include <iostream>
#include <ir/program.hpp>
#include <spdlog/spdlog.h>

Program::Program(const AST& ast, const SymbolTable& symTable)
{
    spdlog::info("IR Program building beginning");
    // Build IR program from ast and symbol table
    // Create functions (first child of root should be dec_list)
    for (const AST* ast : ast.children[0]->children) {
        if (ast->label == AST::function) {
            this->functions.emplace(ast);
        }
    }
    spdlog::info("IR Program building done");
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