#include <string>
#include <vector>
#include <map>
#include <parsetree.hpp>

class AST
{
private:
    static const std::vector<std::string> str;
public:
    enum Label {
        root, function, id, list, declaration, initialization, sum, mul,
        int_const, float_const, string_const, char_const, for_stmt,
        if_stmt, call, int_type, float_type, char_type, bool_expr, unhandled,
        args, return_stmt, le, ge, lt, gt, incr, decr, plus_equal, minus_equal,
        timesequal, dec_list, else_stmt, params
    };

    Label label = Label::unhandled;
    NodeData data;
    std::vector<AST*> children;

    AST(Label label);
    AST(const PTNode* pt);

    void print();
    const std::string toString() const;
};