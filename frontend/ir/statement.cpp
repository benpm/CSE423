#include <ir/statement.hpp>
#include <unordered_map>
#include <spdlog/fmt/fmt.h>

std::unordered_map<Statement::Type, std::string> typeMap {
    {Statement::ADD, "ADD"},
    {Statement::MUL, "MUL"},
    {Statement::DIV, "DIV"},
    {Statement::SUB, "SUB"},
    {Statement::MOD, "MOD"},
    {Statement::MINUS, "MINUS"},
    {Statement::NOT, "NOT"},
    {Statement::ASSIGN, "ASSIGN"},
    {Statement::JUMP, "JUMP"},
    {Statement::JUMP_IF_LT, "JUMP_IF_LT"},
    {Statement::JUMP_IF_GT, "JUMP_IF_GT"},
    {Statement::JUMP_IF_LE, "JUMP_IF_LE"},
    {Statement::JUMP_IF_GE, "JUMP_IF_GE"},
    {Statement::JUMP_IF_EQ, "JUMP_IF_EQ"},
    {Statement::JUMP_IF_NEQ, "JUMP_IF_NEQ"},
    {Statement::JUMP_IF_TRUE, "JUMP_IF_TRUE"},
    {Statement::RETURN, "RETURN"},
    {Statement::BREAK, "BREAK"},
    {Statement::CALL, "CALL"},
    {Statement::NO_OP, "NO_OP"}
};

std::string Arg::toString() const
{
    switch (this->type) {
        case LABEL:     return fmt::format("<{}>", val.label);
        case INT:       return fmt::format("{}", val.ival);
        case CHAR:      return fmt::format("{}", val.cval);
        case FLOAT:     return fmt::format("{}", val.fval);
        case NAME:      return fmt::format("{}", val.sval);
        default:        return "???";
    }
}

Statement::Statement(Type type)
{
    this->type = type;
}

Statement::Statement(Type type, Arg a)
{
    this->type = type;
    this->args.push_back(a);
}

Statement::Statement(Type type, Arg a, Arg b)
{
    this->type = type;
    this->args.push_back(a);
    this->args.push_back(b);
}

Statement::Statement(Type type, Arg a, Arg b, Arg c)
{
    this->type = type;
    this->args.push_back(a);
    this->args.push_back(b);
    this->args.push_back(c);
}

Statement::Statement(Type type, std::vector<Arg>& args)
{
    this->type = type;
    this->args = args;
}

std::string Statement::toString() const
{
    std::string string;
    string += fmt::format("<[{}]", typeMap.at(this->type));
    for (const Arg& arg : args) {
        string += fmt::format(",{}", arg.toString());
    }
    string += ">";
    return string;
}