#include <iostream>
#include <set>
#include <ast.hpp>

std::set<PTNode::Label> terms{
    PTNode::DECLARATION_LIST, PTNode::DECLARATION, PTNode::VAR_DECLARATION,
    PTNode::FUN_DECLARATION, PTNode::PARAM_LIST, PTNode::STATEMENT_LIST,
    PTNode::STATEMENT, PTNode::SCOPED_VAR_DECLARATION, PTNode::REL_EXPRESSION
};

void traversePT(AST* ast, const PTNode* node)
{
    for (const PTNode* child : node->children) {
        // If is non-terminal and is not in set of allowed non-terminals, we can skip
        if ((!child->terminal && terms.find(child->label) == terms.end())
            || child->label == PTNode::NONE) {
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
AST::AST(const PTNode* pt)
{
    this->label = "PROGRAM";
    traversePT(this, pt);
}

void AST::print()
{
    printASTNode(this, 0);
}
