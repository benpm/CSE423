#include <unordered_set>
#include <assert.h>
#include <ir/function.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

void addJumpsToBreaks(
    std::vector<BasicBlock*>::iterator start, 
    std::vector<BasicBlock*>::iterator end,
    uint label);
Arg expand(BasicBlock* block, const AST* ast, uint& tempn);

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
 * @brief Populates a basic block by expanding nested operations in a given AST, creating temporaries
 * 
 * @param block The basic block to add statements to
 * @param ast The AST to generate statements from
 * @param tempn A counter for generating contiguous temporary var names
 * @return Arg A temporary variable that is intended to store the result of the op in the given AST
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
    std::string tempName = fmt::format("#{}", tempn);
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

/**
 * @brief Search for break blocks that need jump statements added to them
 * 
 * @param start An iterator for the first block to search through
 * @param end An iterator for the last block to search through
 * @param label The label we want to jump to (should be the block after the last loop block)
 */
void addJumpsToBreaks(
    std::vector<BasicBlock*>::iterator start, 
    std::vector<BasicBlock*>::iterator end,
    uint label)
{
    for (auto it = start; it != end; ++it) {
        BasicBlock* block = *it;
        if (block->name == "break" && block->statements.size() == 0) {
            block->statements.emplace_back(Statement::JUMP, Arg(label));
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
uint Function::constructWhile(const AST* ast, uint tempn)
{
    assert(ast->label == AST::while_stmt);
    assert(ast->children.size() == 3);

    size_t begin = this->blocks.size();
    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition block
    uint lastTemp = 0;
    BasicBlock* condBlock = new BasicBlock(ast->lineNum, tempn++, "while_cond", condNode->inScope);
    Arg condResult = expand(condBlock, condNode, lastTemp);
    this->blocks.push_back(condBlock);

    // Create declaration and body blocks
    tempn = populateBB(declNode, tempn);
    tempn = populateBB(bodyNode, tempn);

    // Create post-execution block
    lastTemp = 0;
    BasicBlock* postBlock = new BasicBlock(ast->lineNum, tempn++, "while_post", condNode->inScope);
    postBlock->statements.emplace_back(
        Statement::JUMP,
        Arg(condBlock->label)
    );
    this->blocks.push_back(postBlock);

    // Add jumps
    condBlock->statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(postBlock->label + 1),
        condResult
    );

    // Populate break statements with jumps
    addJumpsToBreaks(this->blocks.begin() + begin, this->blocks.end(), postBlock->label + 1);

    return tempn;
}



/**
 * @brief Create basic blocks representing a for loop from given AST
 * 
 * @param ast The AST to produce blocks from
 * @param tempn A number used to keep track of block IDs, should be the number after the last added block
 * @return uint The new tempn
 */
uint Function::constructFor(const AST* ast, uint tempn)
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
    tempn = populateBB(initNode, tempn);

    // Create condition block
    uint lastTemp = 0;
    BasicBlock* condBlock = new BasicBlock(ast->lineNum, tempn++, "for_cond", condNode->inScope);
    Arg condResult = expand(condBlock, condNode, lastTemp);
    this->blocks.push_back(condBlock);

    // Create declaration and body blocks
    tempn = populateBB(declNode, tempn);
    tempn = populateBB(bodyNode, tempn);

    // Create post-execution block
    lastTemp = 0;
    BasicBlock* postBlock = new BasicBlock(ast->lineNum, tempn++, "for_post", postNode->inScope);
    expand(postBlock, postNode, lastTemp);
    this->blocks.push_back(postBlock);

    // Add jumps
    condBlock->statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(postBlock->label + 1),
        condResult
    );
    postBlock->statements.emplace_back(
        Statement::JUMP,
        Arg(condBlock->label)
    );

    // Populate break statements with jumps
    addJumpsToBreaks(this->blocks.begin() + begin, this->blocks.end(), postBlock->label + 1);

    return tempn;
}

/**
       │   └─[7] if_stmt
       │     ├─[7] noteq
       │     │ ├─[7] id (n2)
       │     │ └─[7] int_const (10)
       │     ├─[7] dec_list
       │     ├─[7] list
       │     ├─[8] else_if
       │     │ ├─[8] log_and
       │     │ │ ├─[8] le
       │     │ │ │ ├─[8] id (n1)
       │     │ │ │ └─[8] int_const (2)
       │     │ │ └─[8] log_or
       │     │ │   ├─[8] equal
       │     │ │   │ ├─[8] id (G)
       │     │ │   │ └─[8] char_const (H)
       │     │ │   └─[8] noteq
       │     │ │     ├─[8] id (n2)
       │     │ │     └─[8] int_const (100)
       │     │ ├─[8] dec_list
       │     │ └─[8] list
       │     ├─[10] else_if
       │     │ ├─[10] ge
       │     │ │ ├─[10] id (G)
       │     │ │ └─[10] char_const (H)
       │     │ ├─[10] dec_list
       │     │ └─[10] list
       │     └─[11] else_stmt
       │       ├─[11] dec_list
       │       └─[11] list
 **/

uint Function::constructIf(const AST* ast, uint tempn)
{
    assert(ast->label == AST::if_stmt || ast->label == AST::else_if);

    const AST* condNode = ast->children[0];
    const AST* declNode = ast->children[1];
    const AST* bodyNode = ast->children[2];

    // Create condition block
    uint lastTemp = 0;
    BasicBlock* condBlock = new BasicBlock(ast->lineNum, tempn++, ast->toString(), condNode->inScope);
    Arg condResult = expand(condBlock, condNode, lastTemp);
    this->blocks.push_back(condBlock);
    
    // Create body and declarations
    tempn = populateBB(declNode, tempn);
    tempn = populateBB(bodyNode, tempn);
    uint outBlock = tempn;

    for (auto it = ast->children.begin() + 3; it != ast->children.end(); it++) {
        const AST* child = *it;
        if (child->label == AST::else_if) {
            tempn = constructIf(child, tempn);
        } else if (child->label == AST::else_stmt) {
            tempn = populateBB(child, tempn);
        } else {
            spdlog::error("what");
        }
    }

    // Add the jump
    condBlock->statements.emplace_back(
        Statement::JUMP_IF_FALSE,
        Arg(outBlock),
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
uint Function::populateBB(const AST* ast, uint tempn=0)
{
    // Keep track of beginning and end of this new chunk of basic blocks
    int head = this->blocks.size();
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
                BasicBlock* block = new BasicBlock(child->lineNum, tempn++, child->toString(), child->inScope);
                expand(block, child, nextTemp);
                this->blocks.push_back(block);
                break; }
            // These statements require a little more work
            case AST::while_stmt:
                tempn = constructWhile(child, tempn);
                break;
            case AST::for_stmt:
                tempn = constructFor(child, tempn);
                break;
            case AST::if_stmt:
                tempn = constructIf(child, tempn);
                break;
            case AST::break_stmt: {
                BasicBlock* block = new BasicBlock(child->lineNum, tempn++, child->toString(), child->inScope);
                this->blocks.push_back(block);
                break; }

            // Recur
            default:
                tempn = populateBB(child, tempn);
                break;
        }
        tail = this->blocks.size() - 1;
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
    this->scope = funcNode->ownsScope;

    populateBB(funcNode);
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
    for (const BasicBlock* block : blocks) {
        string += " " + block->toString();
    }
    return string;
}
