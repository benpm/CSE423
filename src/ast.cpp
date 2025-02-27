/**
 * @file ast.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of tree structure to represent an AST
 * @date 2020-02-25
 *
 */
#include <iostream>
#include <set>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>
#include <symboltable.hpp>

void expandNodes(AST* ast);

// Map from parsetree label to AST label
const std::map<PT::Label, AST::Label> labelMap {
    {PT::PROGRAM, AST::root},
    {PT::FUN_DECLARATION, AST::function},
    {PT::ID, AST::id},
    {PT::STATEMENT_LIST, AST::list},
    {PT::UNARY_ASSIGN_EXPRESSION, AST::list},
    {PT::UNARY_EXPRESSION, AST::list},
    {PT::UNARY_REL_EXPRESSION, AST::list},
    {PT::LOCAL_DECLARATIONS, AST::dec_list},
    {PT::DECLARATION_LIST, AST::dec_list},
    {PT::SIMPLE_EXPRESSION, AST::list},
    {PT::AND_EXPRESSION, AST::list},
    {PT::SELECTION_STMT, AST::list},
    {PT::VAR_DECL_LIST, AST::dec_list},
    {PT::SCOPED_VAR_DECLARATION, AST::declaration},
    {PT::VAR_DECLARATION, AST::declaration},
    {PT::VAR_DECL_INITIALIZE, AST::initialization},
    {PT::EQUAL, AST::assignment},
    {PT::SUM_EXPRESSION, AST::sum},
    {PT::MUL_EXPRESSION, AST::mul},
    {PT::DIVIDE, AST::divide},
    {PT::MODULO, AST::modulo},
    {PT::INTCONST, AST::int_const},
    {PT::FLOATCONST, AST::float_const},
    {PT::STRINGLIT, AST::string_const},
    {PT::CHARLIT, AST::char_const},
    {PT::SELECTION_STMT, AST::if_stmt},
    {PT::FOR_STMT, AST::for_stmt},
    {PT::WHILE_STMT, AST::while_stmt},
    {PT::REL_EXPRESSION, AST::bool_expr},
    {PT::ARG_LIST, AST::args},
    {PT::PARAMS, AST::params},
    {PT::CALL, AST::call},
    {PT::INT, AST::int_type},
    {PT::FLOAT, AST::float_type},
    {PT::CHAR, AST::char_type},
    {PT::RETURN_STMT, AST::return_stmt},
    {PT::BREAK, AST::break_stmt},
    {PT::LABEL_STMT, AST::label_stmt},
    {PT::GOTO_STMT, AST::goto_stmt},
    {PT::EXPRESSION, AST::list},
    {PT::LE, AST::le},
    {PT::GE, AST::ge},
    {PT::LT, AST::lt},
    {PT::GT, AST::gt},
    {PT::NOTEQ, AST::noteq},
    {PT::ISEQ, AST::equal},
    {PT::INCR, AST::incr},
    {PT::DECR, AST::decr},
    {PT::PLUSEQUAL, AST::plus_equal},
    {PT::MINUSEQUAL, AST::minus_equal},
    {PT::TIMESEQUAL, AST::times_equal},
    {PT::MODEQUAL, AST::mod_equal},
    {PT::DIVEQUAL, AST::div_equal},
    {PT::ELSE_STMT, AST::else_stmt},
    {PT::ELSE_IF, AST::else_if},
    {PT::IF, AST::if_stmt},
    {PT::ELSE_IF_LIST, AST::list},
    {PT::MODULO, AST::modulo},
    {PT::LOGAND, AST::log_and},
    {PT::LOGOR, AST::log_or},
    {PT::MINUS, AST::sub},
    {PT::PLUS, AST::sum},
    {PT::UNARY_MINUS, AST::unary_minus},
    {PT::NOT, AST::log_not},
};

// Parsetree nodes that should be kept no matter what
const std::set<PT::Label> keepNodes {
    PT::RETURN_STMT, PT::ARG_LIST, PT::UNARY_MINUS, PT::PARAMS, PT::DECLARATION_LIST,
    PT::LOCAL_DECLARATIONS, PT::LABEL_STMT
};

// Parsetree nodes that should be mapped and swapped with their parent in the AST
const std::set<PT::Label> swapNodes {
    PT::LE, PT::GE, PT::LT, PT::GT,
    PT::INCR, PT::DECR,
    PT::PLUSEQUAL, PT::MINUSEQUAL, PT::TIMESEQUAL, PT::DIVEQUAL,
    PT::MODEQUAL,
    PT::DIVIDE, PT::MODULO,
    PT::NOTEQ, PT::ISEQ,
    PT::EQUAL, PT::ELSE_IF, PT::IF,
    PT::LOGAND, PT::LOGOR,
    PT::MINUS, PT::PLUS,
    PT::NOT
};

/**
 * Recursively traverses a given parsetree, adding nodes to the given AST
 *
 * @param ast Pointer to the AST to build upon
 * @param node Pointer to the parsetree to traverse
 *
 */
void traversePT(AST* ast, const PT* node)
{
    // Some pt nodes direct AST builder to swap with their parents, this must be done first
    for (const PT* child : node->children) {
        if (swapNodes.find(child->label) != swapNodes.end()) {
            ast->label = labelMap.at(child->label);
            continue;
        }
    }

    // Loop thru children and decide to build or skip
    for (const PT* child : node->children) {
        if (child->label == PT::NONE) continue;

        size_t children = child->children.size();
        bool mapped = labelMap.find(child->label) != labelMap.end();
        bool keep = keepNodes.find(child->label) != keepNodes.end();
        bool noDupeLabel = child->label != node->label;

        // Skip the swap-nodes we found earlier
        if (swapNodes.find(child->label) != swapNodes.end())
            continue;

        // Decide to skip this node or to build AST node from it (see wiki for more info)
        if (((children > 1 || child->terminal) && noDupeLabel && mapped) || (keep && noDupeLabel)
            || (child->label == PT::MUL_EXPRESSION && children > 1)
            || (child->label == PT::SUM_EXPRESSION && children > 1)
            || (child->label == PT::ELSE_IF_LIST && children > 1)) {

            // Create a new AST node representing this pt node (recursive call)
            AST* next = new AST(child, ast);
            next->data = child->data;
            next->lineNum = child->lineNum;

            // Else-if lists are a special case where they must be a child of the parent
            if (next->label == AST::else_if && ast->label == AST::else_if)
                ast->parent->children.emplace_back(next);
            else
                ast->children.emplace_back(next);
        } else {
            traversePT(ast, child);
        }
    }
}

/**
 * Prints the AST node at the given depth, with levels bitflags
 *
 * @param node The AST node to print the label and possibly value of
 * @param depth The current tree depth
 * @param levels A bit flag that represents levels of parents, for drawing
 *
 */
void AST::printNode(const AST* node, int depth, ulong levels)
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
    fmt::print(padding);
    if ((node->label != AST::root) && SymbolTable::scopeCreators.count(node->label))
        fmt::print("[{}] ", node->ownsScope->tableID);
    else if (node->label != AST::root)
        fmt::print("[{}] ", node->inScope->tableID);

    fmt::print("{}", node->toString());
    switch (node->label) {
        case AST::int_const:
            fmt::print(" ({})", node->data.ival);
            break;
        case AST::float_const:
            fmt::print(" ({:f})", node->data.fval);
            break;
        case AST::char_const:
            fmt::print(" ({})", node->data.cval);
            break;
        case AST::id:
        case AST::string_const:
            fmt::print(" ({})", node->data.sval);
            break;
        case AST::unhandled:
            fmt::print("<!!>");
            break;
        default:
            break;
    }
    fmt::print("\n");

    // Recurse on the node's children, update bit flag as needed
    int i = 0;
    for (auto it : node->children) {
        ulong nlevels = levels;
        if ((i > 0 || node->children.size() > 1) && i < node->children.size() - 1)
            nlevels = levels | (1 << depth);
        printNode(it, depth + 1, nlevels);
        i += 1;
    }
}

/**
 * Recursively expands dec_list lists in ast into normal declarations
 *
 * @param ast Pointer to the AST to modify
 *
 */
void expandNodes(AST* ast)
{
    // Recurse
    for (AST* child : ast->children)
        expandNodes(child);

    std::vector<AST*> newNodes;
    for (auto it = ast->children.begin(); it != ast->children.end();) {
        AST* child = *it;
        // If we have a declaration with multiple assignments, add its children as new declarations to parent
        if (child->label == AST::declaration && child->children[1]->label == AST::dec_list) {
            AST::Label typeLabel = child->children[0]->label;

            // Add assignment declaration to parent dec_list
            for (AST* assignment : child->children[1]->children) {
                AST* declaration = new AST(AST::declaration);
                AST* typeNode = new AST(typeLabel);
                declaration->lineNum = assignment->lineNum;
                typeNode->lineNum = assignment->lineNum;

                declaration->children.push_back(typeNode);
                declaration->children.push_back(assignment);
                newNodes.push_back(declaration);
            }

            // Free orphans
            delete child->children[0];
            delete child->children[1];
            it = ast->children.erase(it);
        } else {
            it++;
        }
    }

    // Add the new declarations as children to the parent node
    ast->children.insert(ast->children.begin(), newNodes.begin(), newNodes.end());
}

/**
 * Construct a new single-node tree object with specified label
 *
 * @param label The label of the type of node to construct
 *
 */
AST::AST(AST::Label label)
{
    this->label = label;
}

/**
 * Construct AST from given parsetree
 * @details This constructor should be used from main.
 *
 * @param pt Pointer to the parsetree from which to construct the AST
 *
 */
AST::AST(const PT* pt)
{
    spdlog::info("AST construction beginning");

    if (pt->label == PT::PROGRAM)
        this->label = AST::root;
    traversePT(this, pt);
    expandNodes(this);

    spdlog::info("AST construction done");
}

/**
 * Construct AST from given parsetree
 *
 * @param pt Pointer to the parsetree from which to construct the AST
 * @param parent The parent node of the AST node being constructed
 *
 */
AST::AST(const PT* pt, AST* parent)
{
    this->parent = parent;
    this->label = labelMap.at(pt->label);
    traversePT(this, pt);
}

/**
 * Print this tree to stdout
 *
 */
void AST::print()
{
    printNode(this, 0, 0);
}

/**
 * Return the string representation of this AST
 *
 * @return The string representation
 *
 */
std::string AST::toString() const
{
    return std::string(magic_enum::enum_name(this->label));
}
