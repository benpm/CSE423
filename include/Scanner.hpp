#pragma once

#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

class Scanner {
public:
    enum TokenLabel {
        Identifier,
        Keyword,
        Operator
    };
    typedef std::pair<std::string, TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
private:
    const std::unordered_map<std::string, TokenLabel> labels = 
        std::unordered_map<std::string, TokenLabel>({
        {"for", Keyword},
        {"while", Keyword},
        {"int", Keyword}
    });
    const std::regex pattern = std::regex(
        "([a-zA-Z]\\w*)"            //Identifiers, keywords
        "|(\\d+)"                   //Number literals
        "|(\".*\")"                 //String literals
        "|([=()*{}&,;>+\\[\\].])"   //Operators, symbols
        "|(\\/\\/.*)"               //In-line comments
        );
};