#pragma once

#include <string>
#include <vector>
#include <regex>
#include <set>

class Scanner {
public:
    enum TokenLabel {
        Identifier,
        StringLiteral,
        NumberLiteral,
        CharacterLiteral,
        SpecialSymbol,
        Keyword,
        TypeIdentifier,
        Operator,
    };
    typedef std::pair<std::string, TokenLabel> Token;

    Scanner();
    std::vector<Token> tokenize(std::string source);
    int capturedGroups(std::smatch& match);

private:
    const std::set<std::string> keywords{
        "case", 	"enum",
        "register", "typedef",
        "default", 	"goto",
        "sizeof", 	"volatile",
        "char", 	"extern",
        "return", 	"union",
        "do", 	    "if",
        "static",   "while",
        "struct"
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

    int groups = 7; // XXX REMEMBER TO CHANGE IF YOU F*CK WITH THE REGEX
    const std::regex pattern = std::regex(  
        "([a-zA-Z_$][a-zA-Z_$\\d]*)"//Identifiers, keywords
        "|(\".*\")"                 //String literals
        "|(\\d+)"                   //Number literals
        "|('.')"                    //Character literals
        "|([=()*{}&,;>+\\[\\].])"   //Operators, symbols
        "|(#[a-zA-Z_]+)"            //Pre-processor directives
        "|(\\/\\/.*)"               //In-line comments
        "|(\\/\\*[.\n]*\\*\\/)"     //Block comments
        "|(#include *<.*>)"         //Include statements
        );
};