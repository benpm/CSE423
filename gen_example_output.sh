#!/bin/bash
echo "THIS FILE GENERATES **NEW** REFERENCE FILES"
echo "DO YOU WISH TO OVERWRITE THE REFERENCE FILES? (y/n): "
read response

if [ "$response" != "y" ] && [ "$response" != "Y" ]
then
    echo "Not updating files. Exiting..."
    exit 0
fi

# Flags to output examples for
compilerFlags=(
    t # Tokens
    p # Parse tree
    a # AST
    s # Symbol Table
    r # IR
    or # Optimization
    S # Assembly
    oS # Optimized assembly
)
compilerFlagNames=(
    tokens.txt
    parseTree.txt
    AST.txt
    symbolTable.txt
    IR.txt
    optimization.txt
    assembly.s
    optimized_assembly.s
)

# IR CSV flag
csvFlag=c
csvFlagName=IR.csv

gitRootDir=$(git rev-parse --show-toplevel)
compilerExecutable=$gitRootDir/build/sc64

if [ ! -d "$gitRootDir/build" ]
then
    echo "Please create build dir at $gitRootDir/"
    exit -1
fi

# Build compiler
cd $gitRootDir/build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j

cd $gitRootDir/examples

# Loop over subdirectories in examples
for dir in $(ls -d */)
do
    cd $dir
    cFile=$(find . -type f -name "*.c")
    cFile=${cFile:2}
	printf "%s:\n" $cFile

    # Loop over compiler flags
    for (( i=0; i<${#compilerFlags[@]}; i++ ));
    do 
        flag=${compilerFlags[i]}
        outName=${compilerFlagNames[i]}

        printf "\tGenerating %s\n" $outName

        # Bash magic to get sterr indented on output
        $compilerExecutable -l -$flag $cFile > $outName 2>/dev/null
    done

    printf "\tGenerating %s\n" $csvFlagName
    $compilerExecutable -l $cFile -$csvFlag $csvFlagName 2>/dev/null $csvFlagName

    cd ../
done