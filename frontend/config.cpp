/**
 * @file config.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of Config structure to hold configuration settings
 * @date 2020-03-02
 *
 */
#include <iostream>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include <config.hpp>

// Global to enable scanner token printing
extern bool scannerPrintTokens;

/**
 * Construct the Config from command-line arguments
 *
 * @param argc The number of command-line arguments
 * @param argv Array of command-line argument strings
 *
 */
Config::Config(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "lhtapsrc:")) != -1) {
        switch (opt) {
        // Print usage message
        case 'h':
            this->usage(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        // Print tokens
        case 't':
            this->printTokens = true;
            scannerPrintTokens = true;
            break;
        // Print AST representation
        case 'a':
            this->printAST = true;
            break;
        // Print ParseTree representation
        case 'p':
            this->printParseTree = true;
            break;
        // Suppress log messages (except errors)
        case 'l':
            this->suppressLogs = true;
            spdlog::set_level(spdlog::level::err);
            break;
        // Print the SymbolTable representation
        case 's':
            this->printSymbolTable = true;
            break;
        // Print the program intermediate representation
        case 'r':
            this->printIR = true;
            break;
        case 'c':
            this->outputCSV = optarg;
            break;
        // Unknown option
        default:
            std::cerr << "Unknown flag in command line input. Exiting" << std::endl;
            spdlog::error("Unknown flag in command line input. Exiting");
            this->usage(argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (this->printTokens)
        spdlog::info("Token printing enabled");
    if (this->printAST)
        spdlog::info("Abstract syntax tree printing enabled");
    if (this->printParseTree)
        spdlog::info("Parse tree printing enabled");
    if (this->printSymbolTable)
        spdlog::info("Symbol table printing enabled");
    if (this->printIR)
        spdlog::info("IR printing enabled");
    if (!this->outputCSV.empty())
        spdlog::info("IR output enabled");

    // No file provided
    if (optind >= argc) {
        std::cerr << "Expected file to compile!" << std::endl;
        spdlog::error("No file provided to compile. Exiting");
        exit(EXIT_FAILURE);
    }

    this->file = argv[optind];

    if (this->printTokens)
        spdlog::info("Token printing enabled");
    if (this->printAST)
        spdlog::info("Abstract syntax tree printing enabled");
    if (this->printParseTree)
        spdlog::info("Parse tree printing enabled");
    if (this->printSymbolTable)
        spdlog::info("Symbol table printing enabled");
}

/**
 * Prints usage options of frontend
 *
 * @param exec_name Generally argv[0]
 *
 */
void Config::usage(std::string exec_name) {
    std::cout << "Usage: " << exec_name << " FILE_TO_PARSE [-h] [-t] [-p] [-a] [-s] [-r] [-l]" << std::endl;
    std::cout << "  -h\t Print this help message" << std::endl
              << "  -t\t Print the tokens found in the file" << std::endl
              << "  -p\t Print the parse tree" << std::endl
              << "  -a\t Print the abstract syntax tree" << std::endl
              << "  -s\t Print the symbol table" << std::endl
              << "  -r\t Print the IR" << std::endl
              << "  -l\t Hide logging messages (except errors)" << std::endl;
}
