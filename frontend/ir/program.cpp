#include <iostream>
#include <ir/program.hpp>
#include <spdlog/spdlog.h>

Program::Program(const AST& ast)
{
    spdlog::info("IR Program building beginning");
    // Build IR program from ast and symbol table
    // Create functions (first child of root should be dec_list)
    for (const AST* child : ast.children[0]->children) {
        if (child->label == AST::function) {
            std::string name = child->children[1]->data.sval;
            this->functions.emplace(name, Function(child));
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