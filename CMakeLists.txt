cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX)
find_package(BISON)

include_directories("frontend")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

################################################################################
#
#   Prepare the scanner and parser with FLEX and BISON
#   Results are stored in ${FLEX_scanner_OUTPUTS} and ${BISON_parser_OUTPUTS}
#
###############################################################################
BISON_TARGET(parser frontend/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp)
FLEX_TARGET(scanner frontend/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
add_flex_bison_dependency(scanner parser)

################################################################################
#
#   Build a basic scanner driver, Takes in a file with as argv[1]
#   and tokenizes it
#
###############################################################################
add_executable(scanner
    frontend/scanner.cpp
    ${FLEX_scanner_OUTPUTS}
)

################################################################################
#
#   Builds the frontend driver. Tokenizes input and builds parse tree
#
###############################################################################
add_executable(frontend
    frontend/frontend.cpp
    ${FLEX_scanner_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)
