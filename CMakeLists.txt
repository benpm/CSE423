cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED) 

include_directories("frontend")
include_directories("external")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

####################################################################################
#
#   Prepare the scanner and parser with FLEX and BISON
#   Results are stored in ${FLEX_scanner_OUTPUTS} and ${BISON_parser_OUTPUTS}
#
####################################################################################
BISON_TARGET(parser frontend/flex_bison/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp)
FLEX_TARGET(scanner frontend/flex_bison/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

####################################################################################
#
#   Builds the frontend driver. Tokenizes file given by argv[1]
#   and builds parse tree
#
####################################################################################
add_executable(frontend
    frontend/frontend.cpp
    frontend/parsetree.cpp
    frontend/ast.cpp
    frontend/config.cpp
    frontend/symboltable.cpp
    ${FLEX_scanner_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)