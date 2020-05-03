# CSE423 Compiler Writing
_Benjamin Mastripolito, Haydn Jones, and Steven Anaya_

Documentation and User Manual lives on our [Wiki](https://github.com/benpm/CSE423/wiki)

## Progress
- [x] [Scanner](https://github.com/benpm/CSE423/wiki/Design#scanningparsing) (lexical analyzer)
    - [x] Full token set
- [x] [Parser](https://github.com/benpm/CSE423/wiki/Design#scanningparsing) (syntactic analyzer)
    - [x] Parse tree
    - [x] Abstract syntax tree
    - [x] Symbol table population
- [x] Semantic analyzer
    - [x] Illegal operation checking
    - [x] Unused function/variable checking
    - [x] Scope checking
- [X] [IR generator](https://github.com/benpm/CSE423/wiki/Specification#intermediate-representation)
    - [X] Output IR to file
    - [X] Read in IR from file
- [X] Optimizer
    - [X] Constant propagation
    - [X] Constant folding
- [X] Code generator
    - [X] x86 processor model
    - [X] Instruction selection
    - [X] Register allocation
    - [X] Output x86 ASM

## Examples
Visit the [/examples](/examples) directory for examples of intermediate ouputs.
