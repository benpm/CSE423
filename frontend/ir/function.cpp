#include <ir/function.hpp>

Function::Function(const AST* funcNode)
{
    // Name of function is second child of function
    this->name = funcNode->children[1]->data.sval;
    this->scope = funcNode->ownedScope;
}
