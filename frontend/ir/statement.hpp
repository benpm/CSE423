#pragma once

#include <string>
#include <vector>

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

    Arg(uint label) { type = Type::LABEL; val.label = label; };
    Arg(int ival)   { type = Type::INT; val.ival = ival; };
    Arg(char cval)  { type = Type::CHAR; val.cval = cval; };
    Arg(float fval) { type = Type::FLOAT; val.fval = fval; };
    Arg(char* sval) { type = Type::NAME; val.sval = sval; };

    std::string toString() const;
};

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
    std::vector<Arg> args;

    Statement(Type type);
    Statement(Type type, Arg a);
    Statement(Type type, Arg a, Arg b);
    Statement(Type type, Arg a, Arg b, Arg c);
    Statement(Type type, std::vector<Arg>& args);
    std::string toString() const;
};