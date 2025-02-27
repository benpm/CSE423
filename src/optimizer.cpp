#include <optimizer.hpp>

const std::set<Statement::Type> canEvalTypes {
    Statement::ADD,
    Statement::MUL,
    Statement::DIV,
    Statement::SUB,
    Statement::MOD,
    Statement::MINUS,
    Statement::NOT
};

const std::set<Statement::Type> jumpStmts {
    Statement::JUMP_EQ, Statement::JUMP_NEQ,
    Statement::JUMP_LT, Statement::JUMP_GT,
    Statement::JUMP_LE, Statement::JUMP_GE,
    Statement::JUMP,
    Statement::JUMP_IF_TRUE, Statement::JUMP_IF_FALSE
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
    spdlog::info("Optimizer beginning");

    for (auto& item : program.functions) {
        bool proceed = false;
        do {
            proceed = false;

            // Create contiguous list of statements
            std::vector<std::pair<BasicBlock&, Statement&>> stmts;
            std::set<size_t> jumpBlocks;
            for (BasicBlock& block : item.second.blocks) {
                if (jumpStmts.count(block.statements.back().type)) {
                    jumpBlocks.insert(block.label);
                }
                for (Statement& stmt : block.statements) {
                    stmts.emplace_back(std::pair<BasicBlock&, Statement&>(block, stmt));
                }
            }

            // Perform constant folding
            for (BasicBlock& block : item.second.blocks) {
                proceed = this->foldConstants(block);
            }

            this->propagate(proceed, stmts, jumpBlocks);
        } while (proceed);
    }
    spdlog::info("Optimizer done");
}

void Optimizer::optimize(BasicBlock& block)
{
    bool proceed = false;
    do {
        proceed = false;
        std::vector<std::pair<BasicBlock&, Statement&>> stmts;
        std::set<size_t> jumpBlocks;
        for (Statement& stmt : block.statements) {
            stmts.emplace_back(std::pair<BasicBlock&, Statement&>(block, stmt));
        }
        // Perform constant folding
        proceed = this->foldConstants(block);
        this->propagate(proceed, stmts, jumpBlocks, true);
    } while (proceed);
}

void Optimizer::propagate(
    bool& proceed,
    std::vector<std::pair<BasicBlock&, Statement&>>& stmts,
    std::set<size_t>& jumpBlocks,
    bool onlyRemoveTemps)
{
    const std::set<Statement::Type> resultStmts {
        Statement::ADD, Statement::MUL, Statement::DIV, Statement::SUB,
        Statement::MOD, Statement::MINUS, Statement::NOT, Statement::ASSIGN,
        Statement::CALL
    };

    // Find last constant assignment for each identifier
    std::map<const char*, size_t> lastAssigns;
    for (size_t i = 0; i < stmts.size(); i++) {
        const Statement& stmt = stmts[i].second;
        if (stmt.type == Statement::ASSIGN
            && stmt.args.at(1).type != Arg::NAME) {
            lastAssigns.emplace(stmt.args.at(0).val.sval, i);
        }
    }

    // Perform constant propagation
    std::vector<std::pair<const char*, size_t>> removeStmts;
    for (const auto& pair : lastAssigns) {
        const bool isTemp = (pair.first[0] == '#');
        const char* name = pair.first;
        Arg value = stmts[pair.second].second.args.at(1);
        spdlog::debug("optimizer: <{}={}>", pair.first, value.toString());
        size_t i = pair.second + 1;
        BasicBlock& originBlock = stmts[pair.second].first;
        for (; i < stmts.size(); i++) {
            Statement& stmt = stmts[i].second;
            BasicBlock& block = stmts[i].first;
            // Continue if no args
            if (stmt.args.size() == 0)
                continue;
            // Break if name is the result arg of operation
            if (resultStmts.count(stmt.type)
                && strcmp(stmt.args.at(0).val.sval, name) == 0) {
                break;
            }
            // Find and replace arg with value
            for (size_t argindx = 0; argindx < stmt.args.size(); argindx++) {
                if (stmt.args.at(argindx).type == Arg::NAME 
                    && strcmp(stmt.args.at(argindx).val.sval, name) == 0) {
                    if (jumpBlocks.count(block.label)
                        && block.label != originBlock.label) {
                        spdlog::debug("optimizer: stopping {}", pair.first);
                        goto stop;
                    }
                    spdlog::debug("optimizer: replacing {} in {}", pair.first, stmt.toString());
                    stmt.args.at(argindx) = value;
                    proceed = true;
                }
            }
            // Break if temporary and non-temp assignment
            if (isTemp && stmt.type == Statement::ASSIGN
                && stmt.args.at(0).val.sval[0] != '#'
            ) {
                break;  
            }
        }
        // If we reached the end, remove assignment
        stop:
        if ((i == stmts.size() && !onlyRemoveTemps) || isTemp) {
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
            int lineNum = statement.lineNum;
            statement = Statement(Statement::ASSIGN, statement.args.at(0), result);
            statement.lineNum = lineNum;
            success = true;
        }
    }

    block.statements = statements;
    return success;
}
