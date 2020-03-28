#pragma once

#include <string>
#include <vector>
#include <map>
#include <parsetree.hpp>

// Abstract Syntax Tree class
class AST
{
private:
    // Map from label to string
    static const std::vector<std::string> str;
public:
    // Label indicating type of node
    enum Label {
        root, function, id, list, declaration, initialization, sum, mul,
        int_const, float_const, string_const, char_const, for_stmt,
        if_stmt, call, int_type, float_type, char_type, bool_expr, unhandled,
        args, return_stmt, le, ge, lt, gt, incr, decr, plus_equal, minus_equal,
        times_equal, dec_list, else_stmt, params, while_stmt, break_stmt, label_stmt,
        goto_stmt, modulo, divide, noteq, equal, assignment, else_if, log_and, log_or,
        div_equal, unary_minus, sub, mod_equal, log_not
    };

    // This node's label (default is "unhandled")
    Label label = Label::unhandled;
    // This node's contained data
    NodeData data;
    // Children of this node
    std::vector<AST*> children;
    // Parent of this node
    AST* parent = NULL;
    // Scope (table ID) (this is populated by the Symbol Table builder!)
    int scopeID = -1;
    // Owned scope (also populated by ST builder)
    int ownedScopeID = -1;

    AST(Label label);
    AST(const PT* pt);
    AST(const PT* pt, AST* parent);


    void print();
    const std::string toString() const;
};
