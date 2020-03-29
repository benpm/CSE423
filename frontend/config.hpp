/**
 * @file config.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Configuration class for compiler. Parses command line options
 * @date 2020-03-02
 * 
 */
#pragma once
#include <string>

typedef struct Config {
    bool printAST = false;
    bool printParseTree = false;
    bool printTokens = false;
    bool printSymbolTable = false;
    bool suppressLogs = false;
    std::string file;

    Config(int argc, char **argv);
    void usage(std::string exec_name);
} Config;