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
        bool proceed = false;
        do {
            proceed = false;

            // Create contiguous list of statements
            std::vector<std::pair<BasicBlock&, Statement&>> stmts;
            for (BasicBlock& block : item.second.blocks) {
                if (block.statements.back().type != Statement::JUMP_IF_FALSE)
                for (Statement& stmt : block.statements) {
                    stmts.emplace_back(std::pair<BasicBlock&, Statement&>(block, stmt));
                }
            }

            // Perform constant folding
            for (BasicBlock& block : item.second.blocks) {
                proceed = this->foldConstants(block);
            }

            // Find last constant assignment for each identifier
            std::vector<std::pair<const char*, size_t>> lastAssigns;
            for (size_t i = 0; i < stmts.size(); i++) {
                const Statement& stmt = stmts[i].second;
                if (stmt.type == Statement::ASSIGN
                    && stmt.args.at(1).type != Arg::NAME) {
                    lastAssigns.emplace_back(stmt.args.at(0).val.sval, i);
                }
            }

            // Perform constant propagation
            std::vector<std::pair<const char*, size_t>> removeStmts;
            for (const auto& pair : lastAssigns) {
                const char* name = pair.first;
                Arg value = stmts[pair.second].second.args.at(1);
                size_t i = pair.second + 1;
                for (; i < stmts.size(); i++) {
                    Statement& stmt = stmts[i].second;
                    // Continue if no args
                    if (stmt.args.size() == 0)
                        continue;
                    // Break if name is LHS
                    if (stmt.args.at(0).type == Arg::NAME
                        && strcmp(stmt.args.at(0).val.sval, name) == 0) {
                        break;
                    }
                    // Find and replace arg with value
                    for (size_t argindx = 1; argindx < stmt.args.size(); argindx++) {
                        if (stmt.args.at(argindx).type == Arg::NAME 
                            && strcmp(stmt.args.at(argindx).val.sval, name) == 0) {
                            spdlog::debug(
                                "replace {} -> {}", 
                                stmt.args.at(argindx).toString(), 
                                value.toString());
                            stmt.args.at(argindx) = value;
                            proceed = true;
                        }
                    }
                }
                // If we reached the end, remove assignment
                if (i == stmts.size()) {
                    removeStmts.push_back(pair);
                }
            }

            // Remove statements that were marked
            for (const auto& pair : removeStmts) {
                BasicBlock& block = stmts.at(pair.second).first;
                auto it = block.statements.begin();
                while (it->type != Statement::ASSIGN || strcmp(it->args.at(0).val.sval, pair.first)) {
                    it++;
                }
                block.statements.erase(it);
                proceed = true;
            }
        } while (proceed);
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

bool Optimizer::foldConstants(BasicBlock& block)
{
    std::vector<Statement> statements = block.statements;
    bool success = false;

    // Constant folding
    for (Statement& statement : statements) {
        if (this->canEvaluate(statement)) {
            Arg result = this->evaluate(statement);
            spdlog::debug("fold from: {}", statement.toString());
            int lineNum = statement.lineNum;
            statement = Statement(Statement::ASSIGN, statement.args.at(0), result);
            statement.lineNum = lineNum;
            spdlog::debug("fold to  : {}", statement.toString());
            success = true;
        }
    }

    block.statements = statements;
    return success;
}
