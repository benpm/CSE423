#include <iostream>
#include <Scanner.hpp>

Scanner::Scanner() {}

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
            // Print the token and its label
            std::cout << "[" << token << ", " << tokenLabelToString(tokenLabel) << "]," << std::endl;
            // Store the token-label pair
            tokens.emplace_back(token, tokenLabel);
        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        printf("Regex syntax error\n");
    }

    return tokens;
}

Scanner::TokenLabel Scanner::identifyToken(std::smatch& match)
{
    for (int i = 1; i <= this->regex_groups; i++) {
        // Regex match made
        if (!match.str(i).empty()) {
            // Switch on the regex match group
            switch (i) {
                // 1 Identifiers, keywords, type identifiers
                case 1:
                    if (keywords.find(match.str(i)) != keywords.end()) {
                        return TokenLabel::Keyword;
                    } else if (typeIdentifiers.find(match.str(i)) != typeIdentifiers.end()) {
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

const char *Scanner::tokenLabelToString(TokenLabel tokenLabel)
{
    return tokenLabels.at(tokenLabel);
}