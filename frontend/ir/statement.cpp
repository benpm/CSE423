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
    {Statement::JUMP_IF_TRUE, "JUMP_IF_TRUE"},
    {Statement::JUMP_IF_FALSE, "JUMP_IF_FALSE"},
    {Statement::COMP_LT, "COMP_LT"},
    {Statement::COMP_GT, "COMP_GT"},
    {Statement::COMP_LE, "COMP_LE"},
    {Statement::COMP_GE, "COMP_GE"},
    {Statement::COMP_EQ, "COMP_EQ"},
    {Statement::COMP_NEQ, "COMP_NEQ"},
    {Statement::LOG_OR, "LOG_OR"},
    {Statement::LOG_AND, "LOG_AND"},
    {Statement::RETURN, "RETURN"},
    {Statement::CALL, "CALL"},
    {Statement::NO_OP, "NO_OP"}
};

std::string Arg::toString() const
{
    switch (this->type) {
        case LABEL:     return fmt::format("<{}>", val.label);
        case INT:       return fmt::format("{}", val.ival);
        case CHAR:      return fmt::format("'{}'", val.cval);
        case FLOAT:     return fmt::format("{:f}", val.fval);
        case NAME:      return fmt::format("{}", val.sval);
        default:        return "???";
    }
}

std::string Arg::toCSV() const
{
    switch (this->type) {
        case LABEL:     return fmt::format("{}", val.label);
        case INT:       return fmt::format("{}", val.ival);
        case CHAR:      return fmt::format("'{}'", val.cval);
        case FLOAT:     return fmt::format("{:f}", val.fval);
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
    string += fmt::format("({}) <[{}]", lineNum, typeMap.at(this->type));
    for (const Arg& arg : args) {
        string += fmt::format(", {}", arg.toString());
    }
    string += ">";
    return string;
}

std::string Statement::toCSV() const
{
    std::string string;
    string += fmt::format("stmt,{},{}", lineNum, typeMap.at(this->type));
    for (const Arg& arg : args) {
        string += fmt::format(",{}", arg.toCSV());
    }
    return string;
}
