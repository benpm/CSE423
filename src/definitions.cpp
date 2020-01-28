#include <definitions.hpp>

namespace definitions
{
    //Valid C keywords
    const std::set<std::string> keywords{
        "case",     "enum",
        "register", "typedef",
        "default",  "goto",
        "sizeof",   "volatile",
        "char",     "extern",
        "return",   "union",
        "do",       "if",
        "static",   "switch",
        "for",      "while",
        "struct",   "extern"
    };

    //Valid C type identifiers
    const std::set<std::string> typeIdentifiers{
        "int", "char", "float", "double", "short", "long", "unsigned"
    };

    //Valid C unary operators
    const std::set<std::string> unaryOperators{
        "+", "-", "*", "&", "!", "~"
    };

    //Valid C binary operators
    const std::set<std::string> binaryOperators{
        "+", "-", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=", // arithmetic
        "||", "&&", "<", ">", "<=", ">=", "!=", "==",               // logic
        "|", "&", "^", "<<", ">>", "|=", "&=", "^=", "<<=", ">>=",  // bitwise
        ".", "->"                                                   // access
    };

    //Valid C ternary operators
    const std::set<std::string> ternaryOperators{
        "?", ":"
    };

    //C special symbols
    const std::set<std::string> specialSymbols{
        "{", "}", "[", "]", "(", ")", ";", ","
    };
}
