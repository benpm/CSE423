#include <optimizer.hpp>

const std::set<Statement::Type> canEvalTypes {
    Statement::ADD,
    Statement::MUL,
    Statement::DIV,
    Statement::SUB,
    Statement::MOD,
    Statement::MINUS,
    Statement::NOT,
    Statement::COMP_LT,
    Statement::COMP_GT,
    Statement::COMP_LE,
    Statement::COMP_GE,
    Statement::COMP_EQ,
    Statement::COMP_NEQ,
    Statement::LOG_OR,
    Statement::LOG_AND
};

template<class T>
T internalEval(const Statement& statement)
{
    switch (statement.type) {
        case Statement::ADD:
            return (T)statement.args.at(1) + (T)statement.args.at(2);
        case Statement::SUB:
            return (T)statement.args.at(1) - (T)statement.args.at(2);
        case Statement::MUL:
            return (T)statement.args.at(1) * (T)statement.args.at(2);
        case Statement::DIV:
            return (T)statement.args.at(1) / (T)statement.args.at(2);
        case Statement::MOD:
            return (int)statement.args.at(1) % (int)statement.args.at(2);
        case Statement::MINUS:
            return -(T)statement.args.at(1);
        case Statement::NOT:
            return !(T)statement.args.at(1);
        case Statement::COMP_LT:
            return (T)statement.args.at(1) < (T)statement.args.at(2);
        case Statement::COMP_LE:
            return (T)statement.args.at(1) <= (T)statement.args.at(2);
        case Statement::COMP_GT:
            return (T)statement.args.at(1) > (T)statement.args.at(2);
        case Statement::COMP_GE:
            return (T)statement.args.at(1) >= (T)statement.args.at(2);
        case Statement::COMP_EQ:
            return (T)statement.args.at(1) == (T)statement.args.at(2);
        case Statement::COMP_NEQ:
            return (T)statement.args.at(1) != (T)statement.args.at(2);
        case Statement::LOG_AND:
            return (T)statement.args.at(1) && (T)statement.args.at(2);
        case Statement::LOG_OR:
            return (T)statement.args.at(1) || (T)statement.args.at(2);
    }
    return T(0);
}

Arg Optimizer::evaluate(const Statement& statement)
{
    switch (statement.resultType) {
        case Symbol::Type::Char:
            return Arg(internalEval<char>(statement));
        case Symbol::Type::Float:
            return Arg(internalEval<float>(statement));
        case Symbol::Type::Int:
            return Arg(internalEval<int>(statement));
    }
    return Arg(0);
}

void Optimizer::optimize(Program& program)
{
    for (auto& item : program.functions) {
        for (BasicBlock& block : item.second.blocks) {
            optimizeBlock(block);
        }
    }
    program.print();
}

bool Optimizer::canEvaluate(const Statement& statement)
{
    if (canEvalTypes.count(statement.type) == 0) {
        return false;
    }
    for (auto it = statement.args.begin() + 1; it != statement.args.end(); it++) {
        if (it->type == Arg::NAME
            || it->type == Arg::LABEL) {
            return false;
        }
    }
    return true;
}

bool Optimizer::optimizeBlock(BasicBlock& block)
{
    std::vector<Statement> statements = block.statements;

    // Constant folding
    for (Statement& statement : statements) {
        if (this->canEvaluate(statement)) {
            Arg result = this->evaluate(statement);
            spdlog::debug("fold from: {}", statement.toString());
            int lineNum = statement.lineNum;
            statement = Statement(Statement::ASSIGN, statement.args.at(0), result);
            statement.lineNum = lineNum;
            spdlog::debug("fold to  : {}", statement.toString());
        }
    }

    block.statements = statements;
    return true;
}
