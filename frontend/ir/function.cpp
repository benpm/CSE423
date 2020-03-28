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
    {AST::log_or,       Statement::LOG_OR},
    {AST::log_and,      Statement::LOG_AND},
    {AST::gt,           Statement::COMP_GT},
    {AST::ge,           Statement::COMP_GE},
    {AST::lt,           Statement::COMP_LT},
    {AST::le,           Statement::COMP_LE},
    {AST::equal,        Statement::COMP_EQ},
    {AST::noteq,        Statement::COMP_NEQ},
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
    AST::assignment, AST::return_stmt,
    AST::plus_equal, AST::minus_equal, AST::incr, AST::decr,
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
            case AST::log_or:
            case AST::log_and:
            case AST::lt:
            case AST::gt:
            case AST::le:
            case AST::ge:
            case AST::equal:
            case AST::noteq:
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

uint populateBB(Function* fun, const AST* ast, uint tempn=0)
{
    // Keep track of beginning and end of this new chunk of basic blocks
    int head = fun->blocks.size();
    int tail = head;

    // Create basic blocks
    for (const AST* child : ast->children) {
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
                BasicBlock* block = new BasicBlock(tempn++, child->toString(), child->scope);
                expand(block, child);
                fun->blocks.push_back(block);
                break; }
            
            // Conditions
            case AST::lt:
            case AST::gt:
            case AST::ge:
            case AST::le:
            case AST::log_and:
            case AST::log_or:
            case AST::log_not: {
                BasicBlock* block = new BasicBlock(tempn++, "cond", child->scope);
                expand(block, child);
                fun->blocks.push_back(block);
                break; }

            // Recurse
            default:
                tempn = populateBB(fun, child, tempn);
                break;
        }
        tail = fun->blocks.size() - 1;
    }

    // Back-populate jumps
    switch (ast->label) {
        case AST::for_stmt: {
            // Jump from condition to body
            fun->blocks.at(head + 1)->statements.push_back(
                Statement(Statement::JUMP_IF_TRUE,
                fun->blocks.at(head + 3)->label,
                (char*)"_0"));
            // Jump from body to post-execution statement
            BasicBlock* jumpStmt = new BasicBlock(tempn++, "for_loop_jump", ast->ownedScope);
            jumpStmt->statements.push_back(
                Statement(Statement::JUMP, fun->blocks.at(head + 2)->label));
            fun->blocks.push_back(jumpStmt);
            // Jump from post-exec statement to condition
            fun->blocks.at(head + 2)->statements.push_back(
                Statement(Statement::JUMP, fun->blocks.at(head + 1)->label));
            break; }
        case AST::while_stmt: {
            // Jump from body to post-execution statement
            BasicBlock* jumpStmt = new BasicBlock(tempn++, "while_loop_jump", ast->ownedScope);
            jumpStmt->statements.push_back(
                Statement(Statement::JUMP, fun->blocks.at(head)->label));
            fun->blocks.push_back(jumpStmt);
            // No-op statement
            BasicBlock* exitBlock = new BasicBlock(tempn++, "break", ast->ownedScope);
            fun->blocks.push_back(exitBlock);
            // Jump from condition out
            fun->blocks.at(head)->statements.push_back(
                Statement(Statement::JUMP_IF_FALSE,
                exitBlock->label,
                (char*)"_0"));
            break; }
    }

    return tempn;
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
    for (const BasicBlock* block : blocks) {
        string += " " + block->toString();
    }
    return string;
}
