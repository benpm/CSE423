/**
 * @file parsetree.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of tree structure to represent a parse tree
 * @date 2020-02-11
 *
 */
#include <iostream>
#include <string>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>
#include <parsetree.hpp>

extern PT* parserYppHandle;
extern int yyparse();
extern FILE *yyin;

/**
 * Constuct a parsetree from a C program file
 *
 * @param filename The filename of the C program
 *
 */
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
 * Construct a parsetree node from given label, children, and line number
 *
 * @param label The label for this node
 * @param children A vector of children (may be empty)
 * @param lineNum The line number associated with this symbol
 *
 */
PT::PT(Label label, std::vector<PT*> children, int lineNum)
    : label(label), children(children), lineNum(lineNum)
{
    terminal = ((int)label <= (int)NONE);
}

/**
 * Construct a parsetree node without any children
 *
 * @param label The label for this leaf node
 * @param lineNum The line number associated with this object
 *
 */
PT::PT(Label label, int lineNum)
    : label(label), lineNum(lineNum)
{
    terminal = ((int)label <= (int)NONE);
}

/**
 * Pretty print the parse tree to standard output
 *
 */
void PT::print()
{
    this->printNode(*this, 0, 0);
}

/**
 * Return the string representation of this node
 *
 * @return The string representation
 *
 */
std::string PT::toString() const
{
    return std::string(magic_enum::enum_name(this->label));
}

/**
 * Pretty print a node and recursively print its children
 * @details Uses a simple prefix DFS tree traversal algorithm
 *
 * @param node Node to recurse on
 * @param depth Current depth
 * @param levels Bit flag used to represent nested levels
 *
 */
void PT::printNode(PT &node, int depth, ulong levels)
{
    if (node.label == NONE)
        return;

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
        case STRINGLIT:
        case ID:
            std::cout << " (" << node.data.sval << ") ";
            break;
    }

    std::cout << std::endl;

    // Recur on the node's children, update bit flag as needed
    int i = 0;
    for (auto it : node.children) {
        ulong nlevels = levels;
        if ((i > 0 || node.children.size() > 1) && i < node.children.size() - 1)
            nlevels = levels | (1 << depth);
        printNode(*it, depth + 1, nlevels);
        i += 1;
    }
}
