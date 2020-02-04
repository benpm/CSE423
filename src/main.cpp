/**
 * @file main.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Driver for our C- compiler
 * 
 */
#include <Scanner.hpp>
#include <fstream>

std::string load_file(std::string path);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Please provide an input file path!\n");
        return -1;
    }

    Scanner scanner;
    std::string source = load_file(argv[1]);

    //Tokenize
    std::vector<Scanner::Token> tokens = scanner.tokenize(source);

    //Print tokens
    for (const Scanner::Token& token : tokens) {
        printf("%16s : %s\n", 
            scanner.tokenLabelToString(token.second).c_str(), 
            token.first.c_str());
    }

    return 0;
}

/**
 * @brief Opens up a file at path and returns a string representation of it
 * 
 * @param path File to be opened
 * @return std::string 
 */
std::string load_file(std::string path)
{
    std::ifstream fileStream(path);
    return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}
