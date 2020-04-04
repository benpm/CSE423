#include <ir/statement.hpp>
#include <unordered_map>
#include <spdlog/fmt/fmt.h>
#include <magic_enum.hpp>

std::string Arg::toString() const
{
    std::string string;
    if (this->type == NAME)
        switch (this->idType) {
            case Symbol::Type::Int: string += "(int)"; break;
            case Symbol::Type::Char: string += "(char)"; break;
            case Symbol::Type::Float: string += "(float)"; break;
        }
    switch (this->type) {
        case LABEL:     string += fmt::format("<{}>", val.label); break;
        case INT:       string += fmt::format("{}", val.ival); break;
        case CHAR:      string += fmt::format("'{}'", val.cval); break;
        case FLOAT:     string += fmt::format("{:f}", val.fval); break;
        case NAME:      string += fmt::format("{}", val.sval); break;
        default:        string += "???"; break;
    }
    return string;
}

std::string Arg::toCSV() const
{
    std::string string;
    if (this->type == NAME)
        switch (this->idType) {
            case Symbol::Type::Int: string += "int "; break;
            case Symbol::Type::Char: string += "char "; break;
            case Symbol::Type::Float: string += "float "; break;
        }
    switch (this->type) {
        case LABEL:     string += fmt::format("{}", val.label); break;
        case INT:       string += fmt::format("{}", val.ival); break;
        case CHAR:      string += fmt::format("'{}'", val.cval); break;
        case FLOAT:     string += fmt::format("{:f}", val.fval); break;
        case NAME:      string += fmt::format("{}", val.sval); break;
        default:        string += "???"; break;
    }
    return string;
}

Statement::Statement(Type type)
{
    this->type = type;
}

Statement::Statement(Type type, Arg a)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
}

Statement::Statement(Type type, Arg a, Arg b)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
    this->args.push_back(b);
}

Statement::Statement(Type type, Arg a, Arg b, Arg c)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
    this->args.push_back(b);
    this->args.push_back(c);
}

Statement::Statement(Type type, std::vector<Arg>& args)
{
    this->type = type;
    this->args = args;
    this->resultType = args.at(0).idType;
}

std::string Statement::toString() const
{
    std::string string;
    // Line number
    string += fmt::format("({}) <", lineNum);
    // Result type
    switch (this->resultType)
    {
        case Symbol::Type::Int: string += "[int]"; break;
        case Symbol::Type::Char: string += "[char]"; break;
        case Symbol::Type::Float: string += "[float]"; break;
    }
    // Statement type
    string += fmt::format("[{}]", magic_enum::enum_name(this->type));
    // Arguments
    for (const Arg& arg : args) {
        string += fmt::format(", {}", arg.toString());
    }
    string += ">";
    return string;
}

std::string Statement::toCSV() const
{
    std::string string;
    string += fmt::format("stmt,{},", lineNum);
    // Result type
    switch (this->resultType)
    {
        case Symbol::Type::Int: string += "int"; break;
        case Symbol::Type::Char: string += "char"; break;
        case Symbol::Type::Float: string += "float"; break;
        default: string += "none"; break;
    }
    // Statement type
    string += fmt::format(",{}", magic_enum::enum_name(this->type));
    // Arguments
    for (const Arg& arg : args) {
        string += fmt::format(",{}", arg.toCSV());
    }
    return string;
}
