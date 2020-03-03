#pragma once
#include <string>

class Config {
public:
    bool printAST = false;
    bool printParseTree = false;
    bool printTokens = false;
    bool suppressLogs = false;
    std::string file;

    Config(int argc, char **argv);
    void usage(std::string exec_name);
};