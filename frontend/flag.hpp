/**
 * @brief Stores flags for compiler use
 * 
 */
#pragma once

namespace Flag {

extern bool tokenPrint;  // Flag indicating whether or not tokens should be printed during compilation
extern bool parserPrint; // Flag indicating whether or not parse tree should be printed during compilation
extern bool astPrint; // Flag indicating whether or not to print AST

}
