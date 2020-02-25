#include <iostream>
#include <set>
#include <ast.hpp>

std::set<Node::NonTerminal> terms{
    Node::DECLARATION_LIST, Node::DECLARATION, Node::VAR_DECLARATION,
    Node::FUN_DECLARATION, Node::PARAM_LIST, Node::STATEMENT_LIST,
    Node::STATEMENT, Node::SCOPED_VAR_DECLARATION, Node::REL_EXPRESSION
};

void traversePT(AST* ast, const Node* node)
{
    for (const Node* child : node->children) {
        // If is non-terminal and is not in set of allowed non-terminals, we can skip
        if ((child->value == Node::NONE && terms.find(child->identifier) == terms.end())
            || child->value == Node::EPSILON) {
            traversePT(ast, child);
        } else {
            AST* next = new AST(child);
            next->label = child->toString();
            ast->children.emplace_back(next);
        }
    }
}

void printASTNode(const AST* node, int depth)
{
    std::cout << std::string(depth * 2, ' ') << node->label << std::endl;
    for (const AST* child : node->children)
    {
        printASTNode(child, depth + 1);
    }
}

AST::AST(std::string label)
{
    this->label = label;
}

/**
 * @brief Construct AST from given parse tree
 */
AST::AST(const Node* pt)
{
    this->label = "PROGRAM";
    traversePT(this, pt);
}

void AST::print()
{
    printASTNode(this, 0);
}
