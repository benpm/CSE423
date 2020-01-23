#include <fstream>
#include <streambuf>
#include <Scanner.hpp>

int main() {
    //Tokenize
    Scanner scanner;
    std::ifstream fileStream("../test_files/test_a.c");
    std::string source((std::istreambuf_iterator<char>(fileStream)),
                        std::istreambuf_iterator<char>());
    std::vector<Scanner::Token> tokens = scanner.tokenize(source);

    //Print tokens
    for (const Scanner::Token& token : tokens) {
        printf("%16s : %s\n", 
            scanner.tokenLabelToString(token.second).c_str(), 
            token.first.c_str());
    }
    return 0;
}