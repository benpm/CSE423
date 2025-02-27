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
#include <spdlog/spdlog.h>

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
    Arg(char* sval, const std::string idType);

    operator int () const { 
        switch (this->type) {
            case Arg::LABEL: return (int)val.label;
            case Arg::CHAR: return (int)val.cval;
            case Arg::FLOAT: return (int)val.fval;
            case Arg::INT: return (int)val.ival;
        }
        spdlog::error("Arg cast used on invalid type");
        return 0;
    }
    operator char () const { 
        switch (this->type) {
            case Arg::LABEL: return (char)val.label;
            case Arg::CHAR: return (char)val.cval;
            case Arg::FLOAT: return (char)val.fval;
            case Arg::INT: return (char)val.ival;
        }
        spdlog::error("Arg cast used on invalid type");
        return 0;
    }
    operator float () const { 
        switch (this->type) {
            case Arg::LABEL: return (float)val.label;
            case Arg::CHAR: return (float)val.cval;
            case Arg::FLOAT: return (float)val.fval;
            case Arg::INT: return (float)val.ival;
        }
        spdlog::error("Arg cast used on invalid type");
        return 0.0f;
    }
    bool operator==(const Arg &other) const { 
        return this->toString() == other.toString();
    }

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
        // Comparison jumps [BB label] [A] [B]
        JUMP_LT, JUMP_GT, JUMP_LE, JUMP_GE, JUMP_EQ, JUMP_NEQ, 
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
