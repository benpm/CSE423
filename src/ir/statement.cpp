/**
 * @file statement.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of IR Statement and Arg data structures
 * @date 2020-03-11
 *
 */
#include <unordered_map>
#include <spdlog/fmt/fmt.h>
#include <magic_enum.hpp>
#include <ir/statement.hpp>
#include <symboltable.hpp>

/**
 * Produce the plaintext string representation of an IR Statement argument
 *
 * @return The plaintext string representation of an IR Statement argument
 *
 */
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

/**
 * Produce the CSV string representation of an IR Statement argument
 *
 * @return The CSV string representation of an IR Statement argument
 *
 */
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

/**
 * Construct a new Statement of a given type
 *
 * @param type The type (operation, etc.) of the statement
 *
 */
Statement::Statement(Type type)
{
    this->type = type;
}

/**
 * Construct a new one-argument Statement of a given type
 *
 * @param type The type (operation, etc.) of the statement
 * @param a The first argument
 *
 */
Statement::Statement(Type type, Arg a)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
}

/**
 * Construct a new two-argument Statement of a given type
 *
 * @param type The type (operation, etc.) of the statement
 * @param a The first argument
 * @param b The second argument
 *
 */
Statement::Statement(Type type, Arg a, Arg b)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
    this->args.push_back(b);
}

/**
 * Construct a new three-argument Statement of a given type
 *
 * @param type The type (operation, etc.) of the statement
 * @param a The first argument
 * @param b The second argument
 * @param c The third argument
 *
 */
Statement::Statement(Type type, Arg a, Arg b, Arg c)
{
    this->type = type;
    this->resultType = a.idType;
    this->args.push_back(a);
    this->args.push_back(b);
    this->args.push_back(c);
}

/**
 * Construct a new variable-argument Statement of a given type (usually a function call)
 *
 * @param type The type (operation, etc.) of the statement
 * @param args A vector of the statement arguments
 *
 */
Statement::Statement(Type type, std::vector<Arg>& args)
{
    this->type = type;
    this->args = args;
    this->resultType = args.at(0).idType;
}

/**
 * Construct a new Statement from its IR CSV representation
 *
 * @param csvRow A reference to the CSV row string stream
 *
 */
Statement::Statement(std::stringstream& csvRow)
{
    std::string value;
    // Store line number
    std::getline(csvRow, value, ',');
    this->lineNum = atoi(value.c_str());
    // Store return type
    std::getline(csvRow, value, ',');
    if (value == "int")
        this->resultType = Symbol::Type::Int;
    else if (value == "float")
        this->resultType = Symbol::Type::Float;
    else if (value == "char")
        this->resultType = Symbol::Type::Char;
    else
        this->resultType = Symbol::Type::None;
    // Store statement type
    std::getline(csvRow, value, ',');
    auto enumType = magic_enum::enum_cast<Type>(value);
    assert(enumType.has_value());
    this->type = enumType.value();
    switch (enumType.value()) {
        case Type::JUMP:
        case Type::JUMP_IF_TRUE:
        case Type::JUMP_IF_FALSE:
            // Store jump label
            std::getline(csvRow, value, ',');
            this->args.emplace_back((uint) atoi(value.c_str()));
    }
    // Get arguments
    while (std::getline(csvRow, value, ',')) {
        if (value.find(' ') != std::string::npos) {
            // Argument is type + label
            std::stringstream arg(value);
            std::string argType;
            std::string argLabel;
            Symbol::Type symType;

            std::getline(arg, argType, ' ');
            std::getline(arg, argLabel, ' ');
            if (argType == "int")
                symType = Symbol::Type::Int;
            else if (argType == "float")
                symType = Symbol::Type::Float;
            else
                symType = Symbol::Type::Char;
            this->args.emplace_back(strdup(argLabel.c_str()), symType);
        } else if (value.find('.') != std::string::npos) {
            // Argument is a float literal
            this->args.emplace_back((float) atof(value.c_str()));
        } else if (value.find('\'') != std::string::npos) {
            // Argument is a char literal
            this->args.emplace_back(value.at(1));
        } else if (isdigit(value.at(0))) {
            // Argument is an int literal
            this->args.emplace_back(atoi(value.c_str()));
        } else {
            // Argument is a name or string literal
            this->args.emplace_back(strdup(value.c_str()));
        }
    }
}

/**
 * Produce the plaintext string representation of the IR Statement
 *
 * @return The plaintext string representation of the IR Statement
 *
 */
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

/**
 * Produce the CSV string representation of the IR Statement
 *
 * @return The CSV string representation of the IR Statement
 *
 */
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
