/**
 * @file statement.hpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Header for Statement and Arg data structures
 * @date 2020-03-11
 *
 */
#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <symboltable.hpp>

/**
 * @brief Data structure for an IR statement argument
 * @details Usually consists of a literal or symbol with a type
 *
 */
struct Arg
{
    // Stored value of argument
    union Val {
        uint label;
        int ival;
        char cval;
        float fval;
        char* sval;
    };
    Val val;

    // Type of argument
    enum Type {
        LABEL, INT, CHAR, FLOAT, NAME
    };
    Type type;

    // Type of identifier
    Symbol::Type idType = Symbol::Type::None;

    Arg(uint label) { type = Type::LABEL; val.label = label; };
    Arg(int ival)   { type = Type::INT; val.ival = ival; idType = Symbol::Type::Int; };
    Arg(char cval)  { type = Type::CHAR; val.cval = cval; idType = Symbol::Type::Char; };
    Arg(float fval) { type = Type::FLOAT; val.fval = fval; idType = Symbol::Type::Float; };
    Arg(char* sval) { type = Type::NAME; val.sval = sval; };
    Arg(char* sval, Symbol::Type idType)
        { type = Type::NAME; val.sval = sval; this->idType = idType; };

    std::string toString() const;
    std::string toCSV() const;
};

/**
 * @brief Data structure for an IR statement
 * @details Consists of a line number, result type, operation, and arguments
 *
 */
class Statement
{
public:
    enum Type {
        // Binary operator [result] [operand A] [operand B]
        ADD, MUL, DIV, SUB, MOD,
        // Unary operator [result] [operand]
        MINUS, NOT, ASSIGN,
        // Unconditional jump to basic block label [BB label]
        JUMP,
        // Boolean comparison, store result [result] [operand A] [operand B]
        COMP_LT, COMP_GT, COMP_LE, COMP_GE, COMP_EQ, COMP_NEQ, LOG_OR, LOG_AND,
        // Conditional true/false jump to basic block label [BB label] [check]
        JUMP_IF_TRUE, JUMP_IF_FALSE,
        // Return statement [return value]
        RETURN,
        // Function call with arguments [result] [function] [args...]
        CALL,
        // Do nothing
        NO_OP
    };

    Type type = Type::NO_OP;
    Symbol::Type resultType = Symbol::Type::None;
    std::vector<Arg> args;
    int lineNum = -1;

    Statement(Type type);
    Statement(Type type, Arg a);
    Statement(Type type, Arg a, Arg b);
    Statement(Type type, Arg a, Arg b, Arg c);
    Statement(Type type, std::vector<Arg>& args);
    Statement(std::stringstream& csvRow);
    std::string toString() const;
    std::string toCSV() const;
};
