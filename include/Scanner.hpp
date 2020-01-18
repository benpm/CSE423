#pragma once

#include <string>
#include <vector>
#include <regex>

class Scanner {
private:
    const std::regex pattern = std::regex(
        "([a-zA-Z]\\w*)"            //Identifiers, keywords
        "|(\\d+)"                   //Number literals
        "|(\".*\")"                 //String literals
        "|([=()*{}&,;>+\\[\\].])"   //Operators, symbols
        "|(\\/\\/.*)"               //In-line comments
        );
public:
    enum TokenLabel {
        Identifier,
        Operator
    };
    typedef std::pair<std::string, Scanner::TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
};