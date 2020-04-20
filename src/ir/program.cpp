/**
 * @file program.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of IR Program data structure
 * @date 2020-03-11
 *
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ir/program.hpp>
#include <spdlog/spdlog.h>

/**
 * Construct a new Program from the program AST
 *
 * @param ast Reference to the AST root node
 *
 */
Program::Program(const AST& ast) : globals(0, -1, "globals")
{
    spdlog::info("IR building beginning");
    // Build IR program from ast and symbol table
    // Create functions (first child of root should be dec_list)
    for (const AST* child : ast.children[0]->children) {
        if (child->label == AST::function) {
            std::string name = child->children[1]->data.sval;
            this->functions.emplace_back(name, Function(child));
        } else if (child->label == AST::declaration) {
            globals.expand(child->children[1]);
        }
    }

    spdlog::info("IR building done");
}

/**
 * Construct a new Program from its CSV representation
 *
 * @param filename The name of the IR CSV file
 *
 */
Program::Program(std::string filename) : globals(0, -1, "globals")
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
        // Get the function name
        std::getline(row, value, ',');
        std::string funcName = value;
        // Get parameters
        std::vector<Arg> parameters;
        while (std::getline(row, value, ',')) {
            std::string idtype = value.substr(0, value.find(' '));
            std::string name = value.substr(value.find(' ') + 1);
            parameters.emplace_back(strdup(name.c_str()), idtype);
        }
        // Create function, passing ref to ifstream
        this->functions.emplace_back(value, Function(funcName, csv, parameters));
    }

    csv.close();
}

/**
 * Produce the plaintext string representation of the IR Program
 *
 * @return The plaintext string representation of the IR Program
 *
 */
std::string Program::outputToString()
{
    // Create plaintext representation of this IR program
    std::string string;
    string += globals.toString() + "\n";
    for (auto item : functions) {
        string += item.second.toString() + "\n";
    }
    return string;
}

/**
 * Output the IR CSV representation to a file
 *
 * @param filename The name of the IR CSV file
 *
 */
void Program::outputToFile(std::string filename)
{
    // Create/overwrite file with CSV representation of IR program
    std::ofstream csv(filename, std::ofstream::out | std::ofstream::trunc);
    std::string string;

    string += this->globals.toCSV();

    for (auto item : functions) {
        string += item.second.toCSV();
    }
    string += "\n";
    csv << string;
    csv.close();
}

/**
 * Print the plaintext string representation of the IR Program
 *
 */
void Program::print()
{
    std::cout << outputToString() << std::endl;
}
