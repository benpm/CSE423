#include <unordered_set>
#include <assert.h>
#include <ir/function.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

uint populateBB(Function* fun, const AST* ast, uint tempn);
uint constructWhile(Function* fun, const AST* ast, uint tempn);

// Mapping from ast nodes to IR statements
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
    {AST::args,         Statement::CALL},
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
Arg expand(BasicBlock* block, const AST* ast, uint& tempn)
{
    std::vector<Arg> args;
    Arg temporary(0u);

    // Function calls
    if (ast->label == AST::call) {
        // Add function identifier to args
        args.push_back(Arg(ast->children[0]->data.sval));
        // Set current ast node to the args child so that function args can be added properly
        ast = ast->children[1];
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
            case AST::call:
                args.push_back(expand(block, child, tempn));
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

    // Create temporary if this is not a final statement
    std::string tempName = fmt::format("_{}", tempn);
    temporary.type = Arg::Type::NAME;
    temporary.val.sval = strdup(tempName.c_str());
    if (endStatements.find(ast->label) == endStatements.end()) {
        args.insert(args.begin(), temporary);
        tempn += 1;
    }

    // Special behavior for specific types of statements
    switch (ast->label) {
        // Add a one to increment, decrement, as they are mapped to add and sub
        case AST::incr:
        case AST::decr:
            args.push_back(Arg(1));
        
        // Make these assign var to self
        case AST::plus_equal:
        case AST::minus_equal:
        case AST::mod_equal:
        case AST::div_equal:
        case AST::times_equal:
            args.insert(args.begin(), args.at(0));
            break;
    }

    // Generate statement
    if (labelMap.find(ast->label) != labelMap.end())
        block->statements.emplace_back(labelMap.at(ast->label), args);

    return temporary;
}

uint constructWhile(Function* fun, const AST* ast, uint tempn)
{
    assert(ast->label == AST::while_stmt);
    assert(ast->children.size() == 3);

    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition block
    uint lastTemp = 0;
    BasicBlock* condBlock = new BasicBlock(tempn++, "while_cond", condNode->scope);
    Arg condResult = expand(condBlock, condNode, lastTemp);
    fun->blocks.push_back(condBlock);

    // Create declaration and body blocks
    tempn = populateBB(fun, declNode, tempn);
    tempn = populateBB(fun, bodyNode, tempn);
    BasicBlock* lastBlock = fun->blocks.back();

    // Add jumps
    condBlock->statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(lastBlock->label + 1),
        condResult
    );

    return tempn;
}

/**
 * @brief Recursively populates a function with basic blocks using a given AST
 * 
 * @param fun The function to populate
 * @param ast The AST to use
 * @param tempn A convenience variable used to create contiguous basic block IDs
 * @return uint The next number to use for basic block ID
 */
uint populateBB(Function* fun, const AST* ast, uint tempn=0)
{
    // Keep track of beginning and end of this new chunk of basic blocks
    int head = fun->blocks.size();
    int tail = head;
    // Next number to be used for temporary variable names
    uint nextTemp = 0;

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
            case AST::assignment:
            case AST::lt:
            case AST::gt:
            case AST::ge:
            case AST::le:
            case AST::log_and:
            case AST::log_or:
            case AST::log_not: {
                BasicBlock* block = new BasicBlock(tempn++, child->toString(), child->scope);
                expand(block, child, nextTemp);
                fun->blocks.push_back(block);
                break; }
            case AST::while_stmt:
                tempn = constructWhile(fun, child, tempn);
                break;

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
                strdup(fmt::format("_{}", nextTemp - 1).c_str())));
            // Jump from body to post-execution statement
            BasicBlock* jumpStmt = new BasicBlock(tempn++, "for_loop_jump", ast->ownedScope);
            jumpStmt->statements.push_back(
                Statement(Statement::JUMP, fun->blocks.at(head + 2)->label));
            fun->blocks.push_back(jumpStmt);
            // Jump from post-exec statement to condition
            fun->blocks.at(head + 2)->statements.push_back(
                Statement(Statement::JUMP, fun->blocks.at(head + 1)->label));
            break; }
    }

    return tempn;
}

/**
 * @brief Construct a new Function, populating with basic blocks using the given AST
 * 
 * @param funcNode AST node, must be of type "function"
 */
Function::Function(const AST* funcNode)
{
    assert(funcNode->label == AST::function);

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
