cmake_minimum_required(VERSION 3.0)

project("CSE423_Compiler")

include_directories("include")

add_executable(
    "main"
    "src/main.cpp"
    "src/definitions.cpp"
    "src/Scanner.cpp"
)
