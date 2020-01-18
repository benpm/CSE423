#include <iostream>
#include <Scanner.hpp>

Scanner::Scanner() {

}

std::vector<Scanner::Token> Scanner::tokenize(const std::string source) {
    std::vector<Scanner::Token> tokens;
    try {
        std::sregex_iterator next(source.begin(), source.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            std::cout << "Match: " << match.str(0)
                << " , " << match.str(1)
                << " , " << match.str(2)
                << " , " << match.str(3)
                << " , " << match.str(4)
                << " , " << match.str(5)
                << std::endl;
            next++;
        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        printf("Regex syntax error\n");
    }
    return tokens;
}