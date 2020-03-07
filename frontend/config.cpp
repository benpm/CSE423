#include <config.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <unistd.h>

// Global to enable scanner token printing
extern bool scannerPrintTokens;

Config::Config(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "lhtaps")) != -1) {
        switch (opt) {
        case 'h':
            this->usage(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        case 't':
            this->printTokens = true;
            scannerPrintTokens = true;
            spdlog::info("Token printing enabled");
            break;
        case 'a':
            this->printAST = true;
            spdlog::info("Abstract syntax tree printing enabled");
            break;
        case 'p':
            this->printParseTree = true;
            spdlog::info("Parse tree printing enabled");
            break;
        case 'l':
            this->suppressLogs = true;
            spdlog::set_level(spdlog::level::err);
            break;
        case 's':
            this->printSymbolTable = true;
            spdlog::info("Symbol table printing enabled");
            break;
        default:
            std::cerr << "Unknown flag in command line input. Exiting" << std::endl;
            spdlog::error("Unknown flag in command line input. Exiting");
            this->usage(argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    // No file provided
    if (optind >= argc) {
        std::cerr << "Expected file to compile!" << std::endl;
        spdlog::error("No file provided to compile. Exiting");
        exit(EXIT_FAILURE);
    }

    this->file = argv[optind];
}

/**
 * @brief Prints usage options of frontend
 *
 * @param exec_name Generally argv[0]
 */
void Config::usage(std::string exec_name) {
    std::cout << "Usage: " << exec_name << " FILE_TO_PARSE [-h] [-t] [-p] [-l] [-s]" << std::endl;
    std::cout << "  -h\t Print this help message" << std::endl
              << "  -t\t Print the tokens found in the file" << std::endl
              << "  -p\t Print the parse tree" << std::endl
              << "  -a\t Print the abstract syntax tree" << std::endl
              << "  -s\t Print the symbol table" << std::endl
              << "  -l\t Hide logging messages (except errors)" << std::endl;
}