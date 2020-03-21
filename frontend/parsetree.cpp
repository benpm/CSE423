/**
 * @file parsetree.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of tree structure to represent a parse tree
 * @date 2020-02-11
 *
 */
#include <iostream>
#include <string>
#include <parsetree.hpp>
#include <spdlog/spdlog.h>

extern PT* parserYppHandle;
extern int yyparse();
extern FILE *yyin;

// Mapping from parsetree label to string
const std::vector<std::string> PT::str {
    "INT", "FLOAT", "CHAR", "FOR", "WHILE", "IF", "ELSE", "RETURN", "BREAK", "GOTO", "SEMICOLON",
    "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "EQUAL", "PLUS",
    "MINUS", "TIMES", "DIVIDE", "MODULO", "PLUSEQUAL", "MINUSEQUAL", "TIMESEQUAL",
    "DIVEQUAL", "MODEQUAL", "INCR", "DECR", "LT", "GT", "LE", "GE", "ISEQ", "NOTEQ", "LOGAND",
    "LOGOR", "NOT", "STRINGLIT", "CHARLIT", "INTCONST", "FLOATCONST", "ID", "ARRAY_ID",
    "EPSILON", "NONE",

    "program", "declaration_list", "declaration", "var_declaration",
    "scoped_var_declaration", "var_decl_list", "var_decl_initialize",
    "var_decl_id", "scoped_type_specifier", "type_specifier",
    "fun_declaration", "params", "param_list", "param_id", "statement",
    "expression_stmt", "expression", "mutable", "assign_op", "unary_assign_op",
    "simple_expression", "and_expression", "unary_rel_expression",
    "rel_expression", "rel_op", "sum_expression", "sum_op", "mul_expression",
    "mul_op", "unary_expression", "factor", "immutable", "call",
    "args", "arg_list", "constant", "compound_stmt", "local_declarations",
    "statement_list", "selection_stmt", "else_if_list", "iteration_stmt",
    "while_stmt", "for_stmt", "return_stmt", "break_stmt", "label_stmt", "goto_stmt",
    "fun_name", "unary_assign_expr", "else_if", "else_stmt", "unary_minus"
};


PT::PT(std::string filename)
{
    // Point FLEX/BISON to file and parse
    spdlog::info("Tokenization/parsing beginning");

    // Try to open file
    FILE *myfile = fopen(filename.c_str(), "r");
    if (!myfile) {
        spdlog::error("Cannot open {}", filename);
        exit(EXIT_FAILURE);
    }

    parserYppHandle = this;
	yyin = myfile;
	yyparse();

    fclose(myfile);
    spdlog::info("Tokenization/parsing done");
}

/**
 * @brief Construct a new parsetree node from given label, children, and lineno
 *
 * @param label The label for this node
 * @param children A vector of children (may be empty)
 * @param lineNum The line number associated with this symbol
 */
PT::PT(Label label, std::vector<PT*> children, int lineNum)
    : label(label), children(children), lineNum(lineNum)
{
    terminal = ((int)label <= (int)NONE);
}

/**
 * @brief Construct a new parsetree node object without any children
 *
 * @param label The label for this leaf node
 * @param lineNum The line number associated with this object
 */
PT::PT(Label label, int lineNum)
    : label(label), lineNum(lineNum)
{
    terminal = ((int)label <= (int)NONE);
}

/**
 * @brief Pretty print the parse tree to standard output
 */
void PT::print()
{
    this->printNode(*this, 0, 0);
}

/**
 * @brief Returns string representation of this node
 *
 * @return String representation
 */
const std::string PT::toString() const
{
    return PT::str.at(this->label);
}

/**
 * @brief Pretty print a node and recursively print its children
 * @details Uses a simple prefix DFS tree traversal algorithm
 *
 * @param node Node to recurse on
 * @param depth Current depth
 * @param levels Bit flag used to represent nested levels
 */
void PT::printNode(PT &node, int depth, ulong levels)
{
    if (node.label == NONE) return;

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
    std::cout << padding << node.toString() << " | Line num: " << node.lineNum;

    // Print the values stored at the nodes, if there are any
    switch (node.label) {
        case INTCONST:
            std::cout << " (" << node.data.ival << ") ";
            break;
        case FLOATCONST:
            std::cout << " (" << node.data.fval << ") ";
            break;
        case CHARLIT:
            std::cout << " (" << node.data.cval << ") ";
            break;
        case ID:
        case STRINGLIT:
            std::cout << " (" << node.data.sval << ") ";
            break;
    }

    std::cout << std::endl;

    // Recurse on the node's children, update bit flag as needed
    int i = 0;
    for (auto it : node.children) {
        ulong nlevels = levels;
        if ((i > 0 || node.children.size() > 1) && i < node.children.size() - 1)
            nlevels = levels | (1 << depth);
        printNode(*it, depth + 1, nlevels);
        i += 1;
    }
}
