cmake_minimum_required(VERSION 3.0)
project("CSE423_Compiler")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

##########################################################
#
#   Locate packages (flex, bison, spdlog)
#
##########################################################
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
    message("-- Static Spdlog not found, falling back to headers. Note that compiling with release will not work")
    include_directories("libs")
else()
    message("-- Static Spdlog found, defaulting to that")
endif()

##########################################################
#
#   Set up includes
#
##########################################################
include_directories("include")
include_directories("libs/magic_enum")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

##########################################################
#
#   Prepare the scanner and parser with FLEX and BISON
#   Results are stored in ${FLEX_scanner_OUTPUTS} and 
#   ${BISON_parser_OUTPUTS}
#
##########################################################
BISON_TARGET(parser 
    src/flex_bison/parser.ypp 
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
)
FLEX_TARGET(scanner 
    src/flex_bison/scanner.l 
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp
)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

##########################################################
#
#   Builds the frontend driver.
#
###########################################################
add_executable(sc64
    "src/frontend.cpp"
    "src/parsetree.cpp"
    "src/ast.cpp"
    "src/config.cpp"
    "src/symboltable.cpp"
    "src/optimizer.cpp"
    "src/ir/statement.cpp"
    "src/ir/basicblock.cpp"
    "src/ir/function.cpp"
    "src/ir/program.cpp"
    ${FLEX_scanner_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)

if(spdlog_FOUND)
    target_link_libraries(sc64 spdlog::spdlog)
endif()
