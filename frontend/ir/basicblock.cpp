#include <ir/basicblock.hpp>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <set>
#include <ast.hpp>

uint BasicBlock::nextTemp = 0;

// AST nodes that will not create temporaries (as opposed to intermediate statements, which do)
const std::set<AST::Label> endStatements {
    AST::assignment, AST::return_stmt,
    AST::plus_equal, AST::minus_equal, AST::incr, AST::decr,
    AST::mod_equal, AST::times_equal, AST::mod_equal, AST::div_equal
};

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

BasicBlock::BasicBlock(int lineNum, uint label, std::string name, SymbolTable* scope)
{
    this->lineNum = lineNum;
    this->scope = scope;
    this->label = label;
    this->name = name;
}

/**
 * @brief Populates a basic block by expanding nested operations in a given AST, creating temporaries
 * 
 * @param block The basic block to add statements to
 * @param ast The AST to generate statements from
 * @param tempn A counter for generating contiguous temporary var names
 * @return Arg A temporary variable that is intended to store the result of the op in the given AST
 */
Arg BasicBlock::expand(const AST* ast)
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
                args.push_back(this->expand(child));
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
    std::string tempName = fmt::format("#{:X}", BasicBlock::nextTemp);
    temporary.type = Arg::Type::NAME;
    temporary.val.sval = strdup(tempName.c_str());
    if (!endStatements.count(ast->label)) {
        args.insert(args.begin(), temporary);
        BasicBlock::nextTemp += 1;
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
    if (labelMap.count(ast->label))
        this->statements.emplace_back(labelMap.at(ast->label), args);

    return temporary;
}

std::string BasicBlock::toString() const
{
    std::string string;
    std::string padding((this->scope->getDepth() - 1) * 3, ' ');
    string += padding + fmt::format("BB{} [{}] ({})\n", this->label, this->name, this->scope->name);
    for (const Statement& stmt : statements) {
        string += padding + " │" + stmt.toString() + "\n";
    }
    string += padding + " └────────────────────\n";
    return string;
}
