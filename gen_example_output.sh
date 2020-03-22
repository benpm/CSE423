#!/bin/bash
# Flags to output examples for
compilerFlags=(
    t # Tokens
    p # Parse tree
    a # AST
    s # Symbol Table
)
compilerFlagNames=(
    tokens
    parseTree
    AST
    symbolTable
)

gitRootDir=$(git rev-parse --show-toplevel)
compilerExecutable=$gitRootDir/build/frontend

cd $gitRootDir/examples

# Loop over subdirectories in examples
for dir in $(ls -d */)
do
    cd $dir
    cFile=$(find . -type f -name "*.c")
    cFile=${cFile:2}
	printf "Generating output for: %s\n" $cFile

    # Loop over compiler flags
    for (( i=0; i<${#compilerFlags[@]}; i++ ));
    do 
        flag=${compilerFlags[i]}
        flagName=${compilerFlagNames[i]}
        outName=${cFile%".c"}_$flagName.txt

        $($compilerExecutable -l -$flag $cFile > $outName)
    done

    cd ../
done