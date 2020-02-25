#include <iostream>
#include <set>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>

std::set<PTNode::Label> keepTerms {
    PTNode::DECLARATION_LIST, PTNode::DECLARATION, PTNode::VAR_DECLARATION,
    PTNode::FUN_DECLARATION, PTNode::PARAM_LIST, PTNode::STATEMENT_LIST,
    PTNode::STATEMENT, PTNode::SCOPED_VAR_DECLARATION, PTNode::REL_EXPRESSION
};

std::set<PTNode::Label> ignoreTerms {
    PTNode::EQUAL
};

void traversePT(AST* ast, const PTNode* node)
{
    for (const PTNode* child : node->children) {
        // If is non-terminal and is not in set of allowed non-terminals, we can skip
        if ((!child->terminal && keepTerms.find(child->label) == keepTerms.end())
            || child->label == PTNode::NONE) {
            traversePT(ast, child);
        } else if (ignoreTerms.find(child->label) == ignoreTerms.end()) {
            AST* next = new AST(child);
            next->label = child->toString();
            next->data = child->data;
            switch (child->label) {
                case PTNode::INTCONST:
                    next->label = fmt::format("({})", child->data.ival);
                    break;
                case PTNode::FLOATCONST:
                    next->label = fmt::format("({})", child->data.fval);
                    break;
                case PTNode::CHARLIT:
                    next->label = fmt::format("({})", child->data.cval);
                    break;
                case PTNode::ID:
                case PTNode::STRINGLIT:
                    next->label = fmt::format("({})", child->data.sval);
                    break;
            }
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
