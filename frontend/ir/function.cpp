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
    {AST::assignment,   Statement::ASSIGN}
};

Arg assignment(BasicBlock* block, const AST* ast, uint tempn=0)
{
    std::vector<Arg> args;
    Arg result(0u);

    for (const AST* child : ast->children) {
        switch (child->label) {
            case AST::mul:
            case AST::modulo:
            case AST::sum:
            case AST::divide:
            case AST::unary_minus:
            case AST::log_not:
                args.push_back(assignment(block, child, tempn + 1));
                break;
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

    // Bail if node not supported
    if (labelMap.find(ast->label) == labelMap.end()) {
        spdlog::warn("AST node {} not supported for IR generation", ast->toString());
        return result;
    }

    // Create temporary if this is an operation
    if (ast->label != AST::assignment) {
        std::string tempName = fmt::format("_{}", tempn);
        result.type = Arg::Type::NAME;
        result.val.sval = strdup(tempName.c_str());
        args.insert(args.begin(), result);
    }

    // Generate statement
    block->statements.emplace_back(labelMap.at(ast->label), args);

    return result;
}

void populateBB(Function* fun, const AST* list)
{
    // Create basic blocks
    for (const AST* child : list->children) {
        switch (child->label) {
            case AST::assignment:{
                BasicBlock* block = new BasicBlock(0, "", child->scope);
                assignment(block, child);
                fun->basicBlocks.push_back(block);
                break;}
            default:
                populateBB(fun, child);
                break;
        }
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
