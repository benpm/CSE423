/**
 * @file frontend.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for scanner + parser. Takes in filename as argv[1] and builds parse tree
 * @date 2020-02-11
 * 
 */
#include <cstring>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include <flag.hpp>
#include <ast.hpp>
#include <parsetree.hpp>

extern PTNode* pt;
extern int yyparse();
extern FILE *yyin;

bool Flag::tokenPrint = false;
bool Flag::parserPrint = false;
bool Flag::astPrint = false;

void yyerror(const char *s);
void usage(char *exec_name);


int main(int argc, char **argv) {
    // Logging configuration
    spdlog::set_default_logger(spdlog::stderr_color_mt("console"));
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[frontend][%^%l%$] %v");

    // Ensure enough args were passed
    if (argc < 2) {
        spdlog::error("No file provided!");
        usage(argv[0]);

        return -1;
    }

    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            spdlog::info("Help message\nUsage: {} filepath [-h] [-t] [-a] [-p]", argv[0]);
            return 0;
        } else if (!strcmp(argv[i], "-t")) {
            Flag::tokenPrint = true;
            spdlog::info("Token printing enabled");
        } else if (!strcmp(argv[i], "-p")) {
            Flag::parserPrint = true;
            spdlog::info("Parse tree printing enabled");
        } else if (!strcmp(argv[i], "-a")) {
            Flag::astPrint = true;
            spdlog::info("Abstract syntax tree printing enabled");
        } else if (!strcmp(argv[i], "-l")) {
            spdlog::set_level(spdlog::level::err);
        } else {
            spdlog::error("Option not recognized: {}\n"
                          "Usage: {} filepath [-h] [-t] [-a] [-p]", argv[i], argv[0]);
            return -1;
        }
    }

    // Try to open file
    FILE *myfile = fopen(argv[1], "r");
    if (!(myfile)) {
        spdlog::error("Cannot open {}", argv[1]);
        usage(argv[0]);

        return -1;
    }

    spdlog::info("Frontend begin");

    // Point FLEX/BISON to file and parse
	yyin = myfile;
	yyparse();

    // Create abstract syntax tree
    AST ast(pt);

    // Print parse tree if requested
    if (Flag::parserPrint) {
        pt->print();
    }
    if (Flag::astPrint) {
        ast.print();
    }

    spdlog::info("Frontend exit");

    return 0;
}

/**
 * @brief Error function called if one is encountered during parsing
 * 
 * @param s Error string
 */
void yyerror(const char *s) {
	spdlog::error("Parser error: {}", s);
	exit(-1);
}
/**
 * @brief Prints usage options of frontend
 * 
 * @param exec_name Generally argv[0]
 */
void usage(char *exec_name) {
    std::cout << "Usage: " << exec_name << " FILE_TO_PARSE [-h] [-t] [-p] [-l]" << std::endl;
    std::cout << "  -h\t Print this help message" << std::endl
              << "  -t\t Print the tokens found in the file" << std::endl
              << "  -p\t Print the parse tree" << std::endl
              << "  -a\t Print the abstract syntax tree" << std::endl
              << "  -l\t Hide logging messages (except errors)" << std::endl;
}