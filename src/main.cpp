#include <Scanner.hpp>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Please provide an input file path!");
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