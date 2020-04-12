/**
 * @file config.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header Config class for compiler. Parses command line options.
 * @date 2020-03-02
 *
 */
#pragma once

#include <string>

struct Config {
    bool printAST = false;
    bool printParseTree = false;
    bool printTokens = false;
    bool printSymbolTable = false;
    bool printIR = false;
    bool optimize = false;
    bool suppressLogs = false;

    std::string file;
    std::string inputCSV;
    std::string outputCSV;

    Config(int argc, char **argv);
    void usage(std::string exec_name);
};
