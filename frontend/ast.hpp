#include <string>
#include <vector>
#include <parsetree.hpp>

class AST
{
public:
    std::string label;

    std::vector<AST*> children;

    AST(std::string label);
    AST(const PTNode* pt);

    void print();
};