#pragma once

#include <string>
#include <vector>


class Scanner {
public:
    enum TokenLabel {
        Indentifier,
        Operator
    };
    typedef std::pair<std::string, Scanner::TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
};