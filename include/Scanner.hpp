#pragma once

#include <string>
#include <vector>
#include <regex>

class Scanner {
public:
    //Labels (types) of tokens
    enum TokenLabel {
        Identifier,
        Keyword,
        TypeIdentifier,
        StringLiteral,
        NumberLiteral,
        CharacterLiteral,
        Comment,
        Operator,
        SpecialSymbol,
        PreprocessorDirective,
        Invalid
    };

    //Token type
    typedef std::pair<std::string, TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
    static std::string tokenLabelToString(TokenLabel tokenLabel);

private:
    TokenLabel identifyToken(std::smatch& match);
    static const std::vector<const char*> tokenLabels;
    static const int regex_groups;
    static const std::regex pattern;
};
