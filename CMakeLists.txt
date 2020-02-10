cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX)


include_directories("include")

add_executable(
    "main"
    "src/main.cpp"
    "src/definitions.cpp"
    "src/Scanner.cpp"
)

FLEX_TARGET(scanner src/scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)

add_executable(scanner2
    ${FLEX_scanner_OUTPUTS}
 )