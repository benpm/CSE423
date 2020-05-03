# CSE423 Compiler Writing
_Benjamin Mastripolito, Haydn Jones, and Steven Anaya_

Documentation and User Manual lives on our [Wiki](https://github.com/benpm/CSE423/wiki).

NOTE: *To compile without flex and bison, [use the release](https://github.com/benpm/CSE423/releases)*

## Notes on Release Branch
This is the release branch, which does not require flex and bison. Compile and run like you
would normally, but *do not delete* the `lex.yy.cpp`, `parser.tab.cpp`, or `parser.tab.hpp` from `/build`.
This branch also does not include the test scripts.

## Progress
- [x] [Scanner](https://github.com/benpm/CSE423/wiki/Scanner-Parser) (lexical analyzer)
    - [x] Full token set
- [x] [Parser](https://github.com/benpm/CSE423/wiki/Scanner-Parser) (syntactic analyzer)
    - [x] Parse tree
    - [x] Abstract syntax tree
    - [x] Symbol table population
- [x] [Semantic Analyzer](https://github.com/benpm/CSE423/wiki/Semantic-Analyzer)
    - [x] Illegal operation checking
    - [x] Unused function/variable checking
    - [x] Scope checking
- [X] [IR Generator](https://github.com/benpm/CSE423/wiki/Intermediate-Representation)
    - [X] Output IR to file
    - [X] Read in IR from file
- [X] [Optimizer](https://github.com/benpm/CSE423/wiki/Optimizer)
    - [X] Constant propagation
    - [X] Constant folding
- [X] [Code Generator](https://github.com/benpm/CSE423/wiki/Code-Generator)
    - [X] x86 processor model
    - [X] Instruction selection
    - [X] Register allocation
    - [X] Output x86 ASM

## Examples
Visit the [/examples](/examples) directory for examples of intermediate ouputs.
