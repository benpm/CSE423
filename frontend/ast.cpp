#include <iostream>
#include <set>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>

void traversePT(AST* ast, const PTNode* node)
{
    for (const PTNode* child : node->children) {
        if (child->label == PTNode::NONE) continue;

        size_t children = child->children.size();

        // If is non-terminal and is not in set of allowed non-terminals, we can skip
        if ((children > 1 || child->terminal) && (child->label != node->label)) {
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
        } else {
            traversePT(ast, child);
        }
    }
}

void printASTNode(const AST* node, int depth, ulong levels)
{
    std::string padding;

    // Construct the padding string using bit flags
    for (int i = 0; i < depth; ++i) {
        if ((levels >> i) & 1) {
            if (i < depth - 1)
                padding += " │";
            else {
                padding += " ├─";
            }
        } else {
            if (i < depth - 1)
                padding += "  ";
            else
                padding += " └─";
        }
    }

    // Print a graphical depiction of the node in the tree
    std::cout << padding << node->label << std::endl;

    // Recurse on the node's children, update bit flag as needed
    int i = 0;
    for (auto it : node->children) {
        ulong nlevels = levels;
        if ((i > 0 || node->children.size() > 1) && i < node->children.size() - 1)
            nlevels = levels | (1 << depth);
        printASTNode(it, depth + 1, nlevels);
        i += 1;
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
    printASTNode(this, 0, 0);
}
