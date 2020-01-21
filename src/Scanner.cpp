#include <iostream>
#include <Scanner.hpp>

Scanner::Scanner() {

}

std::vector<Scanner::Token> Scanner::tokenize(const std::string source)
{
    std::vector<Scanner::Token> tokens;
    try {
        std::sregex_iterator next(source.begin(), source.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            std::cout << "[" << match.str(0) << "], "
                // << " , " << match.str(1)
                // << " , " << match.str(2)
                // << " , " << match.str(3)
                // << " , " << match.str(4)
                << " , " << match.str(100);
                // << std::endl;
            tokens.emplace_back(match.str(0), TokenLabel::Identifier);
            next++;
        }
        std::cout << std::endl;
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        printf("Regex syntax error\n");
    }

    return tokens;
}

int Scanner::capturedGroups(std::smatch& match)
{
    for (int i = 0; i < this->groups; i++) {
        if (!match.str(i).empty()) {
            return i;
        }
    }

    return -1;
}