#include <string>
#include <vector>
#include <parsetree.hpp>

class AST
{
public:
    std::string label;

    std::vector<AST*> children;

    AST(std::string value);
    AST(const Node* pt);

    void print();
};