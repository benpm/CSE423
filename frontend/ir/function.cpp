#include <unordered_set>
#include <assert.h>
#include <ir/function.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

void addJumpsToBreaks(std::vector<BasicBlock>& blocks, uint label);

/**
 * @brief Search for break blocks that need jump statements added to them
 * 
 * @param start An iterator for the first block to search through
 * @param end An iterator for the last block to search through
 * @param label The label we want to jump to (should be the block after the last loop block)
 */
void addJumpsToBreaks(std::vector<BasicBlock>& blocks, uint label)
{
    for (BasicBlock& block : blocks) {
        if (block.name == "break_stmt" && block.statements.size() == 0) {
            block.statements.emplace_back(Statement::JUMP, Arg(label));
        }
    }
}

/**
 * @brief Create basic blocks representing a while loop from given AST
 * 
 * @param ast The AST to produce blocks from
 * @param tempn A number used to keep track of block IDs, should be the number after the last added block
 * @return uint The new tempn
 */
std::vector<BasicBlock> Function::constructWhile(const AST* ast)
{
    assert(ast->label == AST::while_stmt);
    assert(ast->children.size() == 3);

    size_t begin = this->blocks.size();
    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition block
    BasicBlock condBlock(ast->lineNum, this->nextBlockID++, "while_cond", condNode->inScope);
    Arg condResult = condBlock.expand(condNode);

    // Create declaration and body blocks
    std::vector<BasicBlock> declBlocks = this->populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = this->populateBB(bodyNode);

    // Create post-execution block
    BasicBlock postBlock(ast->lineNum, this->nextBlockID++, "while_post", condNode->inScope);
    postBlock.statements.emplace_back(
        Statement::JUMP,
        Arg(condBlock.label)
    );

    // Add jumps
    condBlock.statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(postBlock.label + 1),
        condResult
    );

    // Populate break statements with jumps
    addJumpsToBreaks(bodyBlocks, postBlock.label + 1);

    // Combine blocks
    std::vector<BasicBlock> blocks;
    blocks.push_back(condBlock);
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.push_back(postBlock);

    return blocks;
}



/**
 * @brief Create basic blocks representing a for loop from given AST
 * 
 * @param ast The AST to produce blocks from
 * @param tempn A number used to keep track of block IDs, should be the number after the last added block
 * @return uint The new tempn
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

    // Create condition block
    BasicBlock condBlock(ast->lineNum, this->nextBlockID++, "for_cond", condNode->inScope);
    Arg condResult = condBlock.expand(condNode);

    // Create declaration and body blocks
    std::vector<BasicBlock> declBlocks  = this->populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = this->populateBB(bodyNode);

    // Create post-execution block
    BasicBlock postBlock(ast->lineNum, this->nextBlockID++, "for_post", postNode->inScope);
    postBlock.expand(postNode);

    // Add jumps
    condBlock.statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(postBlock.label + 1),
        condResult
    );
    postBlock.statements.emplace_back(
        Statement::JUMP,
        Arg(condBlock.label)
    );

    // Populate break statements with jumps
    addJumpsToBreaks(bodyBlocks, postBlock.label + 1);

    // Combine blocks
    std::vector<BasicBlock> blocks;
    blocks.insert(blocks.end(), initBlocks.begin(), initBlocks.end());
    blocks.push_back(condBlock);
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.push_back(postBlock);

    return blocks;
}

std::vector<BasicBlock> Function::constructIf(const AST* ast)
{
    assert(ast->label == AST::if_stmt || ast->label == AST::else_if);

    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition block
    BasicBlock condBlock = BasicBlock(ast->lineNum, this->nextBlockID++, ast->toString(), condNode->inScope);
    Arg condResult = condBlock.expand(condNode);
    
    // Create body and declarations
    std::vector<BasicBlock> declBlocks = populateBB(declNode);
    std::vector<BasicBlock> bodyBlocks = populateBB(bodyNode);

    // Add the jump from condition to after the body
    condBlock.statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(this->nextBlockID),
        condResult
    );

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
    blocks.push_back(condBlock);
    blocks.insert(blocks.end(), declBlocks.begin(), declBlocks.end());
    blocks.insert(blocks.end(), bodyBlocks.begin(), bodyBlocks.end());
    blocks.insert(blocks.end(), elseIfChainBlocks.begin(), elseIfChainBlocks.end());

    return blocks;
}

/**
 * @brief Recursively populates a function with basic blocks using a given AST
 * 
 * @param fun The function to populate
 * @param ast The AST to use
 * @param tempn A convenience variable used to create contiguous basic block IDs
 * @return uint The next number to use for basic block ID
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
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString(), child->inScope);
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
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString(), child->inScope);
                tmp.push_back(block);
                break; }
            case AST::goto_stmt: {
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString(), child->inScope);
                tmp.push_back(block);
                this->gotoBlockLocs.emplace(block.label, child->children[0]->data.sval);
                break; }
            case AST::label_stmt: {
                BasicBlock block(child->lineNum, this->nextBlockID++, child->toString(), child->inScope);
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
 * @brief Construct a new Function, populating with basic blocks using the given AST
 * 
 * @param funcNode AST node, must be of type "function"
 */
Function::Function(const AST* funcNode)
{
    assert(funcNode->label == AST::function);

    // Name of function is second child of function
    this->name = funcNode->children[1]->data.sval;
    this->scope = funcNode->ownsScope;

    this->nextBlockID = 0;
    this->blocks = this->populateBB(funcNode);

    // Populate goto statements with jumps to their respective labels
    for (auto item : this->gotoBlockLocs) {
        this->blocks.at(item.first).statements.emplace_back(
            Statement::JUMP,
            Arg(this->labelBlockLocs.at(item.second))
        );
    }
}

/**
 * @brief Produces a plaintext representation of the IR
 * 
 * @return std::string The plaintext representation
 */
std::string Function::toString() const
{
    std::string string;
    string += fmt::format("{}()\n", this->name);
    for (const BasicBlock& block : blocks) {
        string += " " + block.toString();
    }
    return string;
}
