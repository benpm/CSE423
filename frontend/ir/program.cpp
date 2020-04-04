#include <fstream>
#include <iostream>
#include <ir/program.hpp>
#include <spdlog/spdlog.h>

Program::Program(const AST& ast)
{
    spdlog::info("IR building beginning");
    // Build IR program from ast and symbol table
    // Create functions (first child of root should be dec_list)
    for (const AST* child : ast.children[0]->children) {
        if (child->label == AST::function) {
            std::string name = child->children[1]->data.sval;
            this->functions.emplace_back(name, Function(child));
        }
    }

    spdlog::info("IR building done");
}

Program::Program(std::string irCode)
{
    // Build IR program from plaintext IR code
}

std::string Program::outputToString()
{
    // Create plaintext representation of this IR program
    std::string string;
    for (auto item : functions) {
        string += item.second.toString() + "\n";
    }
    return string;
}


void Program::outputToFile(std::string filename)
{
    // Create/overwrite file with CSV representation of IR program
    std::ofstream csv(filename, std::ofstream::out | std::ofstream::trunc);
    std::string string;
    for (auto item : functions) {
        string += item.second.toCSV() + "\n";
    }
    csv << string;
    csv.close();
}

void Program::print()
{
    std::cout << outputToString() << std::endl;
}
