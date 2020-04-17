/**
 * @file function.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of IR Function data structure
 * @date 2020-03-11
 *
 */
#include <cassert>
#include <sstream>
#include <unordered_set>
#include <assert.h>
#include <ir/function.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>


const std::set<Statement::Type> jumpStmts {
    Statement::JUMP_EQ, Statement::JUMP_NEQ,
    Statement::JUMP_LT, Statement::JUMP_GT,
    Statement::JUMP_LE, Statement::JUMP_GE,
    Statement::JUMP,
    Statement::JUMP_IF_TRUE, Statement::JUMP_IF_FALSE
};

const std::map<AST::Label, Statement::Type> logicMap {
    {AST::noteq, Statement::JUMP_NEQ},
    {AST::equal, Statement::JUMP_EQ},
    {AST::ge, Statement::JUMP_GE},
    {AST::le, Statement::JUMP_LE},
    {AST::gt, Statement::JUMP_GT},
    {AST::lt, Statement::JUMP_LT}
};

void negate(Statement& stmt)
{
    const std::map<Statement::Type, Statement::Type> negationOf {
        {Statement::JUMP_EQ, Statement::JUMP_NEQ},
        {Statement::JUMP_NEQ, Statement::JUMP_EQ},
        {Statement::JUMP_LT, Statement::JUMP_GE},
        {Statement::JUMP_GT, Statement::JUMP_LE},
        {Statement::JUMP_LE, Statement::JUMP_GT},
        {Statement::JUMP_GE, Statement::JUMP_LT},
        {Statement::JUMP_IF_TRUE, Statement::JUMP_IF_FALSE},
        {Statement::JUMP_IF_FALSE, Statement::JUMP_IF_TRUE},
        {Statement::JUMP, Statement::JUMP}
    };

    assert(negationOf.count(stmt.type));

    stmt.type = negationOf.at(stmt.type);
}

/**
 * Search for break blocks that need jump statements added to them
 *
 * @param blocks A vector of blocks to search in
 * @param label The label we want to jump to (should be the block after the last loop block)
 *
 */
void addJumpsToBreaks(std::vector<BasicBlock>& blocks, uint label)
{
    for (BasicBlock& block : blocks) {
        if (block.name == "break_stmt" && block.statements.size() == 0) {
            block.statements.emplace_back(Statement::JUMP, Arg(label));
        }
    }
}

BasicBlock Function::createComparisonBlock(const AST* node, uint jumpto)
{
    BasicBlock block(
        node->lineNum, this->nextBlockID++, node->toString()
    );
    Arg opA = block.expand(node->children[0]);
    Arg opB = block.expand(node->children[1]);
    block.statements.emplace_back(
        logicMap.at(node->label), jumpto, opA, opB
    );
    return block;
}

std::vector<BasicBlock> Function::constructCond(const AST* ast, uint success=0, uint failure=1)
{
    const std::set<AST::Label> logOps { AST::log_or, AST::log_and };

    std::vector<BasicBlock> blocks;
    int logChildren = 0;

    for (const AST* child : ast->children) {
        if (logicMap.count(child->label)) {
            BasicBlock block(child->lineNum, this->nextBlockID++, child->toString());
            Statement::Type stmtType = logicMap.at(child->label);
            Arg opA = block.expand(child->children[0]);
            Arg opB = block.expand(child->children[1]);
            Arg jumpTo(0u);
            if (ast->label == AST::log_and) {
                Statement stmt(stmtType, failure, opA, opB);
                negate(stmt);
                block.statements.push_back(stmt);
            } else {
                Statement stmt(stmtType, success, opA, opB);
                block.statements.push_back(stmt);
            }
            blocks.push_back(block);
        } else if (!logOps.count(child->label)) {
            spdlog::warn("not implemented: should handle identifiers / constants");
        } else if (logOps.count(child->label)) {
            logChildren += 1;
        }
    }

    bool link = (logChildren == 2);
    BasicBlock endBlock(ast->lineNum, this->nextBlockID++, "next");
    
    uint nsuccess = success;
    uint nfailure = failure;
    if (logOps.count(ast->children[0]->label)) {
        if (ast->label == AST::log_and) {
            nsuccess = endBlock.label;
        } else {
            nfailure = endBlock.label;
        }
        std::vector<BasicBlock> newBlocks = this->constructCond(ast->children[0], nsuccess, nfailure);
        blocks.insert(blocks.end(), newBlocks.begin(), newBlocks.end());
    }
    blocks.push_back(endBlock);
    if (logOps.count(ast->children[1]->label)) {
        std::vector<BasicBlock> newBlocks = this->constructCond(ast->children[1], success, failure);
        blocks.insert(blocks.end(), newBlocks.begin(), newBlocks.end());
    }
    if (!link) {
        BasicBlock fall(ast->lineNum, this->nextBlockID++, "fallthrough");
        fall.statements.emplace_back(
            Statement::JUMP,
            ast->label == AST::log_and ? success : failure
        );
        blocks.push_back(fall);
    }

    return blocks;
}

void Function::assignCondLabels(std::vector<BasicBlock>& blocks, uint outLabel, uint bodyLabel)
{
    for (BasicBlock& block : blocks) {
        for (Statement& stmt : block.statements) {
            if (jumpStmts.count(stmt.type)) {
                Arg& labelArg = stmt.args.at(0);
                if (labelArg.val.label == 1u) {
                    labelArg.val.label = outLabel;
                } else if (labelArg.val.label == 0u) {
                    labelArg.val.label = bodyLabel;
                }
            }
        }
    }
}

/**
 * Create basic blocks representing a while loop from given AST
 *
 * @param ast The AST to produce blocks from
 * @return Vector of newly created blocks
 *
 */
std::vector<BasicBlock> Function::constructWhile(const AST* ast)
{
    assert(ast->label == AST::while_stmt);
    assert(ast->children.size() == 3);

    size_t begin = this->blocks.size();
    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition blocks
    std::vector<BasicBlock> condBlocks = this->constructCond(condNode);

    // Create declaration and body blocks
    std::vector<BasicBlock> declBlocks = this->populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = this->populateBB(bodyNode);

    // Create post-execution block
    BasicBlock postBlock(ast->lineNum, this->nextBlockID++, "while_post");
    postBlock.statements.emplace_back(
        Statement::JUMP,
        Arg(condBlocks.at(0).label)
    );

    // Populate jumps for condition blocks
    this->assignCondLabels(condBlocks, postBlock.label + 1, bodyBlocks.at(0).label);

    // Populate break statements with jumps
    addJumpsToBreaks(bodyBlocks, postBlock.label + 1);

    // Combine blocks
    std::vector<BasicBlock> blocks;
    blocks.insert(blocks.end(), condBlocks.begin(), condBlocks.end());
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.push_back(postBlock);

    return blocks;
}

/**
 * Create basic blocks representing a for loop from given AST
 *
 * @param ast The AST to produce blocks from
 * @return Vector of newly created blocks
 *
 */
std::vector<BasicBlock> Function::constructFor(const AST* ast)
{
    assert(ast->label == AST::for_stmt);
    assert(ast->children.size() == 5);

    size_t begin = this->blocks.size();
    const AST* initNode = ast->children[0];
    const AST* condNode = ast->children[1];
    const AST* postNode = ast->children[2];
    const AST* declNode = ast->children[3];
    const AST* bodyNode = ast->children[4];

    // Create initialization block
    std::vector<BasicBlock> initBlocks = this->populateBB(initNode);

    // Create condition blocks
    std::vector<BasicBlock> condBlocks = this->constructCond(condNode);

    // Create declaration and body blocks
    std::vector<BasicBlock> declBlocks  = this->populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = this->populateBB(bodyNode);

    // Create post-execution block
    BasicBlock postBlock(ast->lineNum, this->nextBlockID++, "for_post");
    postBlock.expand(postNode);

    // Add jumps
    this->assignCondLabels(condBlocks, postBlock.label + 1, bodyBlocks.at(0).label);
    postBlock.statements.emplace_back(
        Statement::JUMP,
        Arg(condBlocks.at(0).label)
    );

    // Populate break statements with jumps
    addJumpsToBreaks(bodyBlocks, postBlock.label + 1);

    // Combine blocks
    std::vector<BasicBlock> blocks;
    blocks.insert(blocks.end(), initBlocks.begin(), initBlocks.end());
    blocks.insert(blocks.end(), condBlocks.begin(), condBlocks.end());
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.push_back(postBlock);

    return blocks;
}

/**
 * Create blocks for an if statement (including else-if and else children)
 *
 * @param ast The AST node to create blocks from
 * @return Vector of newly created blocks
 *
 */
std::vector<BasicBlock> Function::constructIf(const AST* ast)
{
    assert(ast->label == AST::if_stmt || ast->label == AST::else_if);

    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition blocks
    std::vector<BasicBlock> condBlocks = this->constructCond(condNode);
    
    // Create body and declarations
    std::vector<BasicBlock> declBlocks = populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = populateBB(bodyNode);

    // Add the jump from condition to after the body
    this->assignCondLabels(condBlocks, this->nextBlockID, bodyBlocks.at(0).label);

    // Create blocks from else-if and else children
    std::vector<BasicBlock> elseIfChainBlocks;
    for (auto it = ast->children.begin() + 3; it != ast->children.end(); it++) {
        const AST* child = *it;
        std::vector<BasicBlock> blocks;
        if (child->label == AST::else_if) {
            blocks = this->constructIf(child);
        } else if (child->label == AST::else_stmt) {
            blocks = this->populateBB(child);
        } else {
            spdlog::error("Unexpected child in If/else if AST node");
        }
        elseIfChainBlocks.insert(elseIfChainBlocks.end(), blocks.begin(), blocks.end());
    }

    // Combine blocks
    std::vector<BasicBlock> blocks;
    blocks.insert(blocks.end(), condBlocks.begin(), condBlocks.end());
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.insert(blocks.end(), elseIfChainBlocks.begin(), elseIfChainBlocks.end());

    return blocks;
}

/**
 * Recursively populates a function with basic blocks using a given AST
 *
 * @param ast The AST to use
 * @return Vector of newly created blocks
 *
 */
std::vector<BasicBlock> Function::populateBB(const AST* ast)
{
    std::vector<BasicBlock> blocks;

    // Create basic blocks
    for (const AST* child : ast->children) {
        std::vector<BasicBlock> tmp;
        switch (child->label) {
            // Simple, compound statements
            case AST::return_stmt:
            case AST::call:
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
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString());
                block.expand(child);
                tmp.push_back(block);
                break; }
            // These statements require a little more work
            case AST::while_stmt:
                tmp = constructWhile(child);
                break;
            case AST::for_stmt:
                tmp = constructFor(child);
                break;
            case AST::if_stmt:
                tmp = constructIf(child);
                break;
            case AST::break_stmt: {
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString());
                tmp.push_back(block);
                break; }
            case AST::goto_stmt: {
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString());
                tmp.push_back(block);
                this->gotoBlockLocs.emplace(block.label, child->children[0]->data.sval);
                break; }
            case AST::label_stmt: {
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString());
                block.statements.emplace_back(Statement::NO_OP);
                tmp.push_back(block);
                this->labelBlockLocs.emplace(child->children[0]->data.sval, block.label);
                break; }
            // Recurse
            default:
                tmp = populateBB(child);
                break;
        }

        blocks.insert(blocks.end(), tmp.begin(), tmp.end());
    }

    return blocks;
}

/**
 * Combine groups of blocks into single blocks safely
 *
 * @return true if blocks were combined, else false
 *
 */
bool Function::combineBlocks()
{
    std::vector<std::pair<size_t, size_t>> blockGroups;
    std::set<uint> jumpDestinations;
    std::set<uint> hasJumps;
    size_t newGroups = 0;

    // Find blocks that are jump destinations
    for (const BasicBlock& block : this->blocks) {
        for (const Statement& statement : block.statements) {
            if (jumpStmts.count(statement.type)) {
                jumpDestinations.insert(statement.args.at(0).val.label);
                hasJumps.insert(block.label);
            }
        }
    }

    // Find block groups to be combined
    for (size_t start = 0; start < this->blocks.size(); start++) {
        const BasicBlock& first = this->blocks.at(start);
        size_t end = start;

        // Find last block that meets group conditions
        do {
            const BasicBlock& current = this->blocks.at(end);
            // Stop if block has a jump
            if (hasJumps.count(current.label)) {
                break;
            }
            // Increase group size
            end += 1;
            // Stop if we have reached end of blocks
            if (end >= this->blocks.size()) {
                end -= 1;
                break;
            }
            // Stop if is jump destination
            const BasicBlock& next = this->blocks.at(end);
            if (jumpDestinations.count(next.label)) {
                end -= 1;
                break;
            }
        } while (true);

        // Add to list of groups
        if (end > start) {
            newGroups += 1;
        }
        blockGroups.emplace_back(start, end);
        start = end;
    }

    // Combine block groups
    std::vector<BasicBlock> newBlocks;
    for (const std::pair<size_t, size_t>& group : blockGroups) {
        // Create first block from first block in group
        BasicBlock& first = this->blocks.at(group.first);
        BasicBlock newBlock(
            first.lineNum,
            first.label,
            group.second > group.first ? "combined" : first.name
        );
        // Add statements to block from following blocks in group
        for (size_t i = group.first; i <= group.second; i++) {
            const BasicBlock& next = this->blocks.at(i);
            newBlock.statements.insert(
                newBlock.statements.end(),
                next.statements.begin(),
                next.statements.end()
            );
        }
        newBlocks.push_back(newBlock);
    }
    this->blocks = newBlocks;

    return newGroups > 0;
}

/**
 * Construct a new Function, populating with basic blocks using the given AST
 *
 * @param funcNode Pointer to the AST node, must be of type "function"
 *
 */
Function::Function(const AST* funcNode)
{
    assert(funcNode->label == AST::function);

    // Name of function is second child of function
    this->name = funcNode->children[1]->data.sval;
    this->scope = funcNode->ownsScope;

    // Add parameters
    for (const auto& item : this->scope->table) {
        if (item.second.category == Symbol::Category::Parameter) {
            this->parameters.emplace_back(
                strdup(item.first.c_str()),
                item.second.symType
            );
        }
    }

    // Create blocks
    this->nextBlockID = 0;
    this->blocks = this->populateBB(funcNode);

    // Populate goto statements with jumps to their respective labels
    for (auto item : this->gotoBlockLocs) {
        this->blocks.at(item.first).statements.emplace_back(
            Statement::JUMP,
            Arg(this->labelBlockLocs.at(item.second))
        );
    }

    // Assign line numbers to statements
    for (BasicBlock& block : this->blocks) {
        for (Statement& statement : block.statements) {
            statement.lineNum = block.lineNum;
        }
    }

    // Combine blocks
    // this->combineBlocks();
}

/**
 * Construct a new Function, populating with basic blocks using the given AST
 * 
 * @param name The name of the function
 * @param csv Reference to the CSV ifstream being parsed
 *
 */
Function::Function(std::string name, std::ifstream& csv, std::vector<Arg> parameters)
{
    this->name = name;
    this->parameters = parameters;
    while (true) {
        std::streampos oldPos = csv.tellg();
        std::string line;

        std::getline(csv, line);
        if (line.empty()) {
            csv.seekg(oldPos);
            break;
        }
        std::stringstream row(line);
        std::string rowType;
        std::getline(row, rowType, ',');
        // Row represents a function line
        if (rowType == "func") {
            csv.seekg(oldPos);
            break;
        }
        // Row represents a basic block line
        assert(rowType == "BB");
        // Get the function name and create a Function object
        // Pass reference to the ifstream to Function
        std::string label;
        std::string name;
        std::getline(row, label, ',');
        std::getline(row, name, ',');
        this->blocks.push_back(BasicBlock(atoi(label.c_str()), name, csv));
    }
}

/**
 * Produces a plaintext string representation of the IR function
 *
 * @return The plaintext string representation of the IR function
 *
 */
std::string Function::toString() const
{
    std::string string;
    // Parameters
    string += fmt::format("{}(", this->name);
    for (const Arg& param : this->parameters) {
        string += param.toString() + ", ";
    }
    string += ")\n";
    // Blocks
    for (const BasicBlock& block : this->blocks) {
        string += " " + block.toString();
    }
    return string;
}

/**
 * Produces a CSV string representation of the IR function
 *
 * @return The CSV string representation of the IR function
 *
 */
std::string Function::toCSV() const
{
    std::string string;
    string += fmt::format("func,{}", this->name);
    // Parameters
    for (const Arg& param : this->parameters) {
        string += "," + param.toCSV();
    }
    string += "\n";
    for (const BasicBlock& block : blocks) {
        string += block.toCSV();
    }
    return string;
}
