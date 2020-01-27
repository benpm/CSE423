#pragma once

#include <string>
#include <vector>
#include <regex>
#include <set>

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
    static const std::set<std::string> keywords;
    static const std::set<std::string> typeIdentifiers;
    static const std::set<std::string> operators;
    static const std::set<std::string> specialSymbols;
    static const int regex_groups;
    static const std::regex pattern;
};

std::string load_file(std::string path);