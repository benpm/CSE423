#include <iostream>
#include <set>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include <ast.hpp>

// Map from label to string
const std::vector<std::string> AST::str {
    "root", "function", "id", "list", "declaration", "initialization", "sum", "mul",
    "int_const", "float_const", "string_const", "char_const", "for_stmt",
    "if_stmt", "call", "int_type", "float_type", "char_type", "bool_expr", "unhandled",
    "args", "return_stmt", "le", "ge", "lt", "gt", "incr", "decr", "plus_equal", "minus_equal",
    "times_equal", "dec_list", "else_stmt", "params", "while_stmt", "break_stmt", "modulo",
    "divide", "noteq", "equal", "assignment", "else_if", "log_and", "log_or", "div_equal",
    "unary_minus", "sub", "mod_equal", "log_not"
};

// Map from parsetree label to AST label
const std::map<PTNode::Label, AST::Label> labelMap {
    {PTNode::PROGRAM, AST::root},
    {PTNode::FUN_DECLARATION, AST::function},
    {PTNode::ID, AST::id},
    {PTNode::STATEMENT_LIST, AST::list},
    {PTNode::UNARY_ASSIGN_EXPRESSION, AST::list},
    {PTNode::UNARY_EXPRESSION, AST::list},
    {PTNode::UNARY_REL_EXPRESSION, AST::list},
    {PTNode::LOCAL_DECLARATIONS, AST::dec_list},
    {PTNode::DECLARATION_LIST, AST::dec_list},
    {PTNode::SIMPLE_EXPRESSION, AST::list},
    {PTNode::AND_EXPRESSION, AST::list},
    {PTNode::SELECTION_STMT, AST::list},
    {PTNode::VAR_DECL_LIST, AST::dec_list},
    {PTNode::SCOPED_VAR_DECLARATION, AST::declaration},
    {PTNode::VAR_DECLARATION, AST::declaration},
    {PTNode::VAR_DECL_INITIALIZE, AST::initialization},
    {PTNode::EQUAL, AST::assignment},
    {PTNode::SUM_EXPRESSION, AST::sum},
    {PTNode::MUL_EXPRESSION, AST::mul},
    {PTNode::DIVIDE, AST::divide},
    {PTNode::MODULO, AST::modulo},
    {PTNode::INTCONST, AST::int_const},
    {PTNode::FLOATCONST, AST::float_const},
    {PTNode::CHARLIT, AST::char_const},
    {PTNode::STRINGLIT, AST::string_const},
    {PTNode::SELECTION_STMT, AST::if_stmt},
    {PTNode::FOR_STMT, AST::for_stmt},
    {PTNode::WHILE_STMT, AST::while_stmt},
    {PTNode::REL_EXPRESSION, AST::bool_expr},
    {PTNode::ARG_LIST, AST::args},
    {PTNode::PARAMS, AST::params},
    {PTNode::CALL, AST::call},
    {PTNode::INT, AST::int_type},
    {PTNode::FLOAT, AST::float_type},
    {PTNode::CHAR, AST::char_type},
    {PTNode::RETURN_STMT, AST::return_stmt},
    {PTNode::BREAK, AST::break_stmt},
    {PTNode::EXPRESSION, AST::list},
    {PTNode::LE, AST::le},
    {PTNode::GE, AST::ge},
    {PTNode::LT, AST::lt},
    {PTNode::GT, AST::gt},
    {PTNode::NOTEQ, AST::noteq},
    {PTNode::ISEQ, AST::equal},
    {PTNode::INCR, AST::incr},
    {PTNode::DECR, AST::decr},
    {PTNode::PLUSEQUAL, AST::plus_equal},
    {PTNode::MINUSEQUAL, AST::minus_equal},
    {PTNode::TIMESEQUAL, AST::times_equal},
    {PTNode::MODEQUAL, AST::mod_equal},
    {PTNode::DIVEQUAL, AST::div_equal},
    {PTNode::ELSE_STMT, AST::else_stmt},
    {PTNode::ELSE_IF, AST::else_if},
    {PTNode::IF, AST::if_stmt},
    {PTNode::ELSE_IF_LIST, AST::list},
    {PTNode::MODULO, AST::modulo},
    {PTNode::LOGAND, AST::log_and},
    {PTNode::LOGOR, AST::log_or},
    {PTNode::MINUS, AST::sub},
    {PTNode::PLUS, AST::sum},
    {PTNode::UNARY_MINUS, AST::unary_minus},
    {PTNode::NOT, AST::log_not},
};

// Parsetree nodes that should be kept no matter what
const std::set<PTNode::Label> keepNodes {
    PTNode::RETURN_STMT, PTNode::ARG_LIST, PTNode::UNARY_MINUS, PTNode::PARAMS, PTNode::DECLARATION_LIST, PTNode::LOCAL_DECLARATIONS
};

// Parsetree nodes that should be mapped and swapped with their parent in the AST
const std::set<PTNode::Label> swapNodes {
    PTNode::LE, PTNode::GE, PTNode::LT, PTNode::GT,
    PTNode::INCR, PTNode::DECR,
    PTNode::PLUSEQUAL, PTNode::MINUSEQUAL, PTNode::TIMESEQUAL, PTNode::DIVEQUAL,
    PTNode::MODEQUAL,
    PTNode::DIVIDE, PTNode::MODULO,
    PTNode::NOTEQ, PTNode::ISEQ,
    PTNode::EQUAL, PTNode::ELSE_IF, PTNode::IF,
    PTNode::LOGAND, PTNode::LOGOR,
    PTNode::MINUS, PTNode::PLUS,
    PTNode::NOT
};

/**
 * @brief Recursively traverses a given parsetree, adding nodes to the given AST
 *
 * @param ast The AST to build upon
 * @param node The parsetree to traverse
 */
void traversePT(AST* ast, const PTNode* node)
{
    // Some pt nodes direct AST builder to swap with their parents, this must be done first
    for (const PTNode* child : node->children) {
        if (swapNodes.find(child->label) != swapNodes.end()) {
            ast->label = labelMap.at(child->label);
            continue;
        }
    }

    // Loop thru children and decide to build or skip
    for (const PTNode* child : node->children) {
        if (child->label == PTNode::NONE) continue;

        size_t children = child->children.size();
        bool mapped = labelMap.find(child->label) != labelMap.end();
        bool keep = keepNodes.find(child->label) != keepNodes.end();
        bool noDupeLabel = child->label != node->label;

        // Skip the swap-nodes we found earlier
        if (swapNodes.find(child->label) != swapNodes.end())
            continue;

        // Decide to skip this node or to build AST node from it (see wiki for more info)
        if (((children > 1 || child->terminal) && noDupeLabel && mapped) || (keep && noDupeLabel)
            || (child->label == PTNode::MUL_EXPRESSION && children > 1)
            || (child->label == PTNode::ELSE_IF_LIST && children > 1)) {

            // Create a new AST node representing this pt node (recursive call)
            AST* next = new AST(child, ast);
            next->data = child->data;

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
 * @brief Prints the AST node at the given depth, with levels bitflags
 *
 * @param node The AST node to print the label and possibly value of
 * @param depth The current tree depth
 * @param levels A bit flag that represents levels of parents, for drawing
 */
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
    fmt::print(padding);
    if (node->scopeID > -1 && node->label == AST::id)
        fmt::print("[{}] ", node->scopeID);
    fmt::print("{}", node->toString());
    switch (node->label) {
        case AST::int_const:
            fmt::print(" ({})", node->data.ival);
            break;
        case AST::float_const:
            fmt::print(" ({})", node->data.fval);
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
    }
    fmt::print("\n");

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

/**
 * @brief Construct a new single-node tree object with specified label
 *
 * @param label
 */
AST::AST(AST::Label label)
{
    this->label = label;
}

/**
 * @brief Construct AST from given parse tree
 *
 * @param pt Parse tree to constr from
 */
AST::AST(const PTNode* pt)
{
    if (pt->label == PTNode::PROGRAM)
        this->label = AST::root;
    traversePT(this, pt);
}

/**
 * @brief Construct AST from given parse tree
 *
 * @param pt Parse tree to constr from
 */
AST::AST(const PTNode* pt, AST* parent)
{
    this->parent = parent;
    this->label = labelMap.at(pt->label);
    traversePT(this, pt);
}

/**
 * @brief Print this tree to stdout
 */
void AST::print()
{
    printASTNode(this, 0, 0);
}

/**
 * @brief Returns string representation of this AST
 *
 * @return String representation
 */
const std::string AST::toString() const
{
    return AST::str.at(this->label);
}
