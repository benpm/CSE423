cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX)
include_directories("include")

########################################
#   Scanner code
########################################
FLEX_TARGET(scanner scanner/scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)

add_executable(scanner
    ${FLEX_scanner_OUTPUTS}
)