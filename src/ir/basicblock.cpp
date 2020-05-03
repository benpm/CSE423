/**
 * @file basicblock.cpp
 * @author Haydn Jones, Benjamin Mastripolito, Steven Anaya
 * @brief Implementation of IR BasicBlock data structure
 * @date 2020-03-11
 *
 */
#include <fstream>
#include <set>
#include <sstream>
#include <ir/basicblock.hpp>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <ast.hpp>

// Value of next unused temporary variable
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
    {AST::plus_equal,   Statement::ADD},
    {AST::minus_equal,  Statement::MINUS},
    {AST::mod_equal,    Statement::MOD},
    {AST::div_equal,    Statement::DIV},
    {AST::times_equal,  Statement::MUL},
    {AST::incr,         Statement::ADD},
    {AST::decr,         Statement::MINUS},
    {AST::assignment,   Statement::ASSIGN},
    {AST::args,         Statement::CALL},
    {AST::call,         Statement::CALL},
    {AST::return_stmt,  Statement::RETURN}
};

Arg createAlias(const AST* idnode)
{
    assert(idnode->label == AST::id);
    // Find the scope in which this identifier is declared
    const SymbolTable* declScope = idnode->inScope;
    while (declScope->table.count(idnode->data.sval) == 0) {
        declScope = declScope->parent;
    }
    // Get the identifier type
    Symbol::Type idType = declScope->table.at(idnode->data.sval).symType;
    // Search further up the tree to find if this identifier is shadowed
    const SymbolTable* scope = declScope->parent;
    while (scope) {
        if (scope->table.count(idnode->data.sval)) {
            std::string newName = fmt::format(".{}.{}", declScope->tableID, idnode->data.sval);
            return Arg(strdup(newName.c_str()), idType);
        }
        scope = scope->parent;
    }
    return Arg(idnode->data.sval, idType);
}

/**
 * Create a simple basic block
 *
 * @param lineNum The line number of the start of the block
 * @param label The unique label (BB#) of the basic block
 * @param name The name (function, if, for, etc.) of the basic block
 *
 */
BasicBlock::BasicBlock(int lineNum, uint label, std::string name)
{
    this->lineNum = lineNum;
    this->label = label;
    this->name = name;
}

/**
 * Create a basic block from an IR CSV representation
 *
 * @param label The unique label (BB#) of the basic block
 * @param name The name (function, if, for, etc.) of the basic block
 * @param csv A reference to the CSV file stream being parsed
 *
 */
BasicBlock::BasicBlock(uint label, std::string name, std::ifstream& csv)
{
    this->label = label;
    this->name = name;
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
        // Row represents a basic block or function line
        if (rowType == "BB" || rowType == "func") {
            csv.seekg(oldPos);
            break;
        }
        // Row represents a statement line
        assert(rowType == "stmt");
        this->statements.push_back(Statement(row));
    }
}

/**
 * Populates a basic block by expanding nested operations in a given AST, creating temporaries
 * 
 * @param ast The AST to generate statements from
 * @return A temporary variable that is intended to store the result of the op in the given AST
 *
 */
Arg BasicBlock::expand(const AST* ast, bool start)
{
    if (start) {
        BasicBlock::nextTemp = 0;
    }
    std::vector<Arg> args;
    Arg temporary(0u);

    // Function calls
    if (ast->label == AST::call) {
        // Set current ast node to the args child so that function args can be added properly
        if (ast->children.size() > 1) {
            // Add function identifier to args
            args.push_back(Arg(ast->children.at(0)->data.sval));
            ast = ast->children.at(1);
        }
    }

    // Constants, identifiers
    switch (ast->label) {
        case AST::id:
            return createAlias(ast);
            break;
        case AST::int_const:
            return Arg(ast->data.ival);
            break;
        case AST::float_const:
            return Arg(ast->data.fval);
            break;
        case AST::char_const:
            return Arg(ast->data.cval);
            break;
        case AST::string_const:
            return Arg(ast->data.sval);
            break;
    }

    // Loop through children and add statement arguments
    for (const AST* child : ast->children) {
        switch (child->label) {
            // Recurse on operations, add returned temporary
            case AST::call:
                temporary.idType = child->inScope->getSymbolType(child->children[0]->data.sval);
            case AST::mul:
            case AST::modulo:
            case AST::sum:
            case AST::sub:
            case AST::divide:
            case AST::unary_minus:
                args.push_back(this->expand(child, false));
                break;
            // Identifier or constant value arguments
            case AST::id:
                args.push_back(createAlias(child));
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
            case AST::log_not:
            case AST::log_or:
            case AST::log_and:
            case AST::lt:
            case AST::gt:
            case AST::le:
            case AST::ge:
            case AST::equal:
            case AST::noteq:
                spdlog::error("Comparison not allowed in assignments! Line {}", child->toString(), child->lineNum);
                exit(EXIT_FAILURE);
                break;
            default:
                spdlog::error("{} unhandled", child->toString());
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Create temporary if this is not a final statement
    std::string tempName = fmt::format("#{:X}", BasicBlock::nextTemp);
    temporary.type = Arg::Type::NAME;
    temporary.val.sval = strdup(tempName.c_str());
    // Type rules
    if (temporary.idType == Symbol::Type::None)
    for (const Arg& arg : args) {
        temporary.idType = std::max(temporary.idType, arg.idType);
    }
    // Insert temporary if needed
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
    if (labelMap.count(ast->label)) {
        if (ast->label == AST::assignment
            && BasicBlock::nextTemp > 0) {
            this->statements.back().args.at(0) = args.at(0);
        } else {
            Statement& stmt = this->statements.emplace_back(labelMap.at(ast->label), args);
            stmt.lineNum = ast->lineNum;
        }
    }

    return temporary;
}

/**
 * Return the "pretty" string representation of an IR basic block
 *
 * @return The string representation of the IR basic block
 *
 */
std::string BasicBlock::toString() const
{
    std::string string;
    std::string padding(1, ' ');
    string += padding + fmt::format("BB{} [{}]\n", this->label, this->name);
    for (const Statement& stmt : statements) {
        string += padding + " │" + stmt.toString() + "\n";
    }
    string += padding + " └────────────────────\n";
    return string;
}

/**
 * Return the CSV string representation of an IR BasicBlock
 *
 * @return The CSV string representation of the IR BasicBlock
 *
 */
std::string BasicBlock::toCSV() const
{
    std::string string;
    string += fmt::format("BB,{},{}\n", this->label, this->name);
    for (const Statement& stmt : statements) {
        string += stmt.toCSV() + "\n";
    }
    return string;
}
