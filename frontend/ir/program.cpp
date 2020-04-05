#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

Program::Program(std::string filename)
{
    spdlog::info("IR building beginning");
    std::ifstream csv(filename);
    std::string line;

    while (std::getline(csv, line) && !line.empty()) {
        std::stringstream row(line);
        std::string value;
        std::getline(row, value, ',');
        // Row represents a function line
        assert(value == "func");
        // Get the function name and create a Function object
        // Pass reference to the ifstream to Function
        std::getline(row, value, ',');
        this->functions.emplace_back(value, Function(value, csv));
    }

    csv.close();
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
        string += item.second.toCSV();
    }
    string += "\n";
    csv << string;
    csv.close();
}

void Program::print()
{
    std::cout << outputToString() << std::endl;
}
