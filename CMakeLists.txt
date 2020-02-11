cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX)
find_package(BISON)
include_directories("scanner" "parser")


# Targets
BISON_TARGET(parser parser/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp)
FLEX_TARGET(scanner scanner/scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)

# Required for anything to work
add_flex_bison_dependency(scanner parser)

add_executable(parser
    ${BISON_parser_OUTPUTS}
)

add_executable(scanner
    scanner/scanner.cpp
    ${FLEX_scanner_OUTPUTS}
)

