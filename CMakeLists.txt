cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")

find_package(FLEX)
find_package(BISON) 

include_directories("frontend")
include_directories("frontend/flex_bison/")
include_directories("external")

####################################################################################
#
#   Prepare the scanner and parser with FLEX and BISON
#   Results are stored in ${FLEX_scanner_OUTPUTS} and ${BISON_parser_OUTPUTS}
#
####################################################################################
if(FLEX_FOUND AND BISON_FOUND)
    message("Flex and Bison found, rebuilding parser if needed")
    FLEX_TARGET(scanner frontend/flex_bison/scanner.l ${PROJECT_SOURCE_DIR}/frontend/flex_bison/lex.yy.cpp)
    BISON_TARGET(parser frontend/flex_bison/parser.ypp ${PROJECT_SOURCE_DIR}/frontend/flex_bison/parser.tab.cpp)
    ADD_FLEX_BISON_DEPENDENCY(scanner parser)
endif()

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
    ${PROJECT_SOURCE_DIR}/frontend/flex_bison/parser.tab.cpp
    ${PROJECT_SOURCE_DIR}/frontend/flex_bison/lex.yy.cpp
)