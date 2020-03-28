#include <unordered_set>
#include <assert.h>
#include <ir/function.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

const std::unordered_map<AST::Label, Statement::Type> labelMap {
    {AST::sum,          Statement::ADD},
    {AST::mul,          Statement::MUL},
    {AST::divide,       Statement::DIV},
    {AST::sub,          Statement::SUB},
    {AST::modulo,       Statement::MOD},
    {AST::unary_minus,  Statement::MINUS},
    {AST::log_not,      Statement::NOT},
    {AST::gt,           Statement::JUMP_IF_GT},
    {AST::ge,           Statement::JUMP_IF_GE},
    {AST::lt,           Statement::JUMP_IF_LT},
    {AST::le,           Statement::JUMP_IF_LE},
    {AST::equal,        Statement::JUMP_IF_EQ},
    {AST::noteq,        Statement::JUMP_IF_NEQ},
    {AST::plus_equal,   Statement::ADD},
    {AST::minus_equal,  Statement::MINUS},
    {AST::mod_equal,    Statement::MOD},
    {AST::div_equal,    Statement::DIV},
    {AST::times_equal,  Statement::MUL},
    {AST::incr,         Statement::ADD},
    {AST::decr,         Statement::MINUS},
    {AST::assignment,   Statement::ASSIGN},
    {AST::return_stmt,  Statement::RETURN}
};

// AST nodes that will not create temporaries (as opposed to intermediate statements, which do)
const std::unordered_set<AST::Label> endStatements {
    AST::assignment, AST::return_stmt, AST::lt, AST::gt, AST::le, AST::ge,
    AST::equal, AST::noteq, AST::plus_equal, AST::minus_equal, AST::incr, AST::decr,
    AST::mod_equal, AST::times_equal, AST::mod_equal, AST::div_equal
};

/**
 * @brief Populates a basic block by expanding nested operations in a given AST
 * 
 * @param block The basic block to add statements to
 * @param ast The AST to generate statements from
 * @param tempn A counter for generating contiguous temporary var names
 * @return Arg A temporary variable that is intended to be the result of the op in the given AST
 */
Arg expand(BasicBlock* block, const AST* ast, uint tempn=0)
{
    std::vector<Arg> args;
    Arg result(0u);

    // Bail if node not supported
    if (labelMap.find(ast->label) == labelMap.end()) {
        spdlog::warn("AST node {} not supported for IR generation", ast->toString());
        return result;
    }

    // Loop through children and add statement arguments
    for (const AST* child : ast->children) {
        switch (child->label) {
            // Recurse on operations, add returned temporary
            case AST::mul:
            case AST::modulo:
            case AST::sum:
            case AST::sub:
            case AST::divide:
            case AST::unary_minus:
            case AST::log_not:
                args.push_back(expand(block, child, tempn + 1));
                break;
            
            // Identifier or constant value arguments
            case AST::id:
                args.emplace_back(child->data.sval);
                break;
            case AST::int_const:
                args.emplace_back(child->data.ival);
                break;
            case AST::float_const:
                args.emplace_back(child->data.fval);
                break;
            case AST::char_const:
                args.emplace_back(child->data.cval);
                break;
            case AST::string_const:
                args.emplace_back(child->data.sval);
                break;
            default:
                spdlog::warn("{} unhandled", child->toString());
                break;
        }
    }

    // Create temporary if this is an operation
    if (endStatements.find(ast->label) == endStatements.end()) {
        std::string tempName = fmt::format("_{}", tempn);
        result.type = Arg::Type::NAME;
        result.val.sval = strdup(tempName.c_str());
        args.insert(args.begin(), result);
    }

    // Special behavior for specific types of statements
    switch (ast->label) {
        case AST::incr:
        case AST::decr:
            args.push_back(Arg(1));
        case AST::plus_equal:
        case AST::minus_equal:
        case AST::mod_equal:
        case AST::div_equal:
        case AST::times_equal:
            args.insert(args.begin(), args.at(0));
            break;
    }

    // Generate statement
    block->statements.emplace_back(labelMap.at(ast->label), args);

    return result;
}

void populateBB(Function* fun, const AST* list)
{
    // Create basic blocks
    uint tempn = 0;
    for (const AST* child : list->children) {
        switch (child->label) {
            // Simple, compound statements
            case AST::return_stmt:
            case AST::incr:
            case AST::decr:
            case AST::plus_equal:
            case AST::minus_equal:
            case AST::mod_equal:
            case AST::div_equal:
            case AST::times_equal:
            case AST::assignment: {
                BasicBlock* block = new BasicBlock(tempn, child->toString(), child->scope);
                expand(block, child);
                fun->basicBlocks.push_back(block);
                break; }
            
            // Conditions
            case AST::lt:
            case AST::gt:
            case AST::ge:
            case AST::le: {
                BasicBlock* block = new BasicBlock(tempn, "cond", child->scope);
                expand(block, child);
                fun->basicBlocks.push_back(block);
                break; }
            default:
                populateBB(fun, child);
                break;
        }
        tempn += 1;
    }
}

Function::Function(const AST* funcNode)
{
    // Name of function is second child of function
    this->name = funcNode->children[1]->data.sval;
    this->scope = funcNode->ownedScope;

    populateBB(this, funcNode);
}

std::string Function::toString() const
{
    std::string string;
    string += fmt::format("{}()\n", this->name);
    for (const BasicBlock* block : basicBlocks) {
        string += " " + block->toString();
    }
    return string;
}
