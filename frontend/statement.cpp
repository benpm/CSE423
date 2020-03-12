#include <statement.hpp>

Statement::Statement(Type type)
{
    this->type = type;
}

Statement::Statement(Type type, ArgVal a)
{
    this->type = type;
    this->args.push_back(a);
}

Statement::Statement(Type type, ArgVal a, ArgVal b)
{
    this->type = type;
    this->args.push_back(a);
    this->args.push_back(b);
}

Statement::Statement(Type type, ArgVal a, ArgVal b, ArgVal c)
{
    this->type = type;
    this->args.push_back(a);
    this->args.push_back(b);
    this->args.push_back(c);
}
