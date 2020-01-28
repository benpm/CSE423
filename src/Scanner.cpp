#include <Scanner.hpp>
#include <definitions.hpp>

//Default constructor
Scanner::Scanner() {}

//Tokenize the input program
std::vector<Scanner::Token> Scanner::tokenize(const std::string source)
{
    std::vector<Scanner::Token> tokens;
    try {
        std::sregex_iterator next(source.begin(), source.end(), pattern);
        std::sregex_iterator end;
        for (; next != end; next++) {
            std::smatch match = *next;
            // Get string of matched token
            std::string token = match.str();
            // Get the token label
            TokenLabel tokenLabel = identifyToken(match);
            // Store the token-label pair
            if (tokenLabel != TokenLabel::Comment)
                tokens.emplace_back(token, tokenLabel);
        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        printf("Regex syntax error\n");
    }

    return tokens;
}

//Returns string name of given label
std::string Scanner::tokenLabelToString(TokenLabel tokenLabel)
{
    return tokenLabels.at(tokenLabel);
}

//Use regex match to determine type of token
Scanner::TokenLabel Scanner::identifyToken(std::smatch& match)
{
    for (int i = 1; i <= this->regex_groups; i++) {
        // Regex match made
        if (!match.str(i).empty()) {
            // Switch on the regex match group
            switch (i) {
                // 1 Identifiers, keywords, type identifiers
                case 1:
                    if (definitions::keywords.find(match.str(i)) != definitions::keywords.end()) {
                        return TokenLabel::Keyword;
                    } else if (definitions::typeIdentifiers.find(match.str(i)) !=
                            definitions::typeIdentifiers.end()) {
                        return TokenLabel::TypeIdentifier;
                    } else {
                        return TokenLabel::Identifier;
                    }
                // 2 String literals
                case 2:
                    return TokenLabel::StringLiteral;
                // 3 Number literals
                case 3:
                    return TokenLabel::NumberLiteral;
                // 4 Character literals
                case 4:
                    return TokenLabel::CharacterLiteral;
                // 5 In-line comments
                case 5:
                // 6 Block comments
                case 6:
                    return TokenLabel::Comment;
                // 7 Operators
                case 7:
                    return TokenLabel::Operator;
                // 8 Special symbols
                case 8:
                    return TokenLabel::SpecialSymbol;
                // 9 Pre-processor directives
                case 9:
                    return TokenLabel::PreprocessorDirective;
            }
        }
    }

    return TokenLabel::Invalid;
}

//Types of tokens
const std::vector<const char*> Scanner::tokenLabels {
    "Identifier", "Keyword", "TypeIdentifier", "StringLiteral",
    "NumberLiteral", "CharacterLiteral", "Comment", "Operator",
    "SpecialSymbol", "PreprocessorDirective", "Invalid"
};

//Number of regex capture groups (change to reflect number of capture groups)
const int Scanner::regex_groups = 9;

//The regex pattern for tokenizing
const std::regex Scanner::pattern = std::regex(  
    "([a-zA-Z_][a-zA-Z_\\d]*)"               // Identifiers, keywords
    "|(\"[\\S\\s]*?\")"                      // String literals
    "|(-?\\d+\\.?\\d*)"                      // Number literals
    "|('.')"                                 // Character literals
    "|(\\/\\/.*)"                            // In-line comments
    "|(\\/\\*[\\S\\s]*\\*\\/)"               // Block comments
    "|(<<=?|>>=?|\\+\\+|--|&&|\\|\\||\\.|->" // Operators
    "|[-+*/=<>!%&\\|^]=?|[?:])"              // More operators
    "|([(){}\\[\\],;])"                      // Special symbols
    "|(#[a-zA-Z_]+ .*)"                      // Pre-processor directives
);
