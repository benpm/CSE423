#pragma once

#include <string>
#include <vector>
#include <regex>
#include <set>

class Scanner {
public:
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

    typedef std::pair<std::string, TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
    TokenLabel identifyToken(std::smatch& match);
    const char *tokenLabelToString(TokenLabel tokenLabel);

private:
    const std::vector<const char*> tokenLabels {
        "Identifier", "Keyword", "TypeIdentifier", "StringLiteral",
        "NumberLiteral", "CharacterLiteral", "Comment", "Operator",
        "SpecialSymbol", "PreprocessorDirective", "Invalid"
    };

    const std::set<std::string> keywords{
        "case",     "enum",
        "register", "typedef",
        "default", 	"goto",
        "sizeof",   "volatile",
        "char",     "extern",
        "return",   "union",
        "do",       "if",
        "static",   "switch",
        "for",      "while",
        "struct",   "extern"
    };

    const std::set<std::string> typeIdentifiers{
        "int", "char", "float", "double", "short", "long", "unsigned"
    };

    const std::set<std::string> operators{
        "+", "-", "/", "*", "+=", "++", "--", "|", "||", "&&", "=",
        "==", "^", "&", "<<", ">>", "%", "!", "~", ".", "<=", ">=",
        "->", "<", ">", "!=", "*=", "/="
    };

    const std::set<std::string> specialSymbols{
        "{", "}", "[", "]", "(", ")", ";", ","
    };

    const int regex_groups = 9; // Remember to change if you modify the regex
    const std::regex pattern = std::regex(  
        "([a-zA-Z_][a-zA-Z_\\d]*)"               // Identifiers, keywords
        "|(\".*\")"                              // String literals
        "|(-?\\d+\\.?\\d*)"                      // Number literals
        "|('.')"                                 // Character literals
        "|(\\/\\/.*)"                            // In-line comments
        "|(\\/\\*[\\S\\s]*\\*\\/)"               // Block comments
        "|(<<=?|>>=?|\\+\\+|--|&&|\\|\\||\\.|->" // Operators
            "|[-+*/=<>!%&\\|^]=?)"               // More operators
        "|([(){}\\[\\],;])"                      // Special symbols
        "|(#[a-zA-Z_]+.*)"                       // Pre-processor directives
    );
};
