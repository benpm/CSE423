#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Flags to output examples for
compilerFlags=(
    t # Tokens
    p # Parse tree
    a # AST
    s # Symbol Table
    r # IR
)
compilerFlagNames=(
    tokens
    parseTree
    AST
    symbolTable
    IR
)

csvFlag=c
csvFlagName=IR.csv

gitRootDir=$(git rev-parse --show-toplevel)
examplesDir=$gitRootDir/examples/
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

# Loop over subdirectories in examples
failed=0
total=0
for dir in $(ls -d $examplesDir*/)
do
    cFile=$(find $dir -type f -name "*.c")
    cFile=${cFile}
	printf "%s:\n" $(basename -- $cFile)

    # Loop over compiler flags
    for (( i=0; i<${#compilerFlags[@]}; i++ ));
    do 
        flag=${compilerFlags[i]}
        flagName=${compilerFlagNames[i]}
        outName=$dir/$flagName.txt

        printf "\tDiffing %s... " $flagName

        # Bash magic to get sterr indented on output
        $compilerExecutable -l -$flag $cFile > "diff_tmp.txt" 2>&1
        diff "diff_tmp.txt" $outName > /dev/null
        if [ "$?" != "0" ]
        then
            printf "${RED}FAILED!${NC}\n"
            inDir=$(basename $dir) 
            printf "+++++++++++++++++++++++++++++ Left: New | Right: Original | %s.c %s +++++++++++++++++++++++++++++\n" $inDir $flagName
            diff "diff_tmp.txt" $outName -y
            failed=$((failed+1))
        else 
            printf "${GREEN}PASSED!${NC}\n"
        fi
        total=$((total+1))
    done

    printf "\tDiffing %s... " $csvFlagName

    # Diff IR CSV
    # Bash magic to get sterr indented on output
    outName=$dir/$csvFlagName
    $compilerExecutable -l $cFile -$csvFlag "diff_tmp.txt" 2> "diff_tmp.txt"
    diff "diff_tmp.txt" $outName > /dev/null
    if [ "$?" != "0" ]
    then
        printf "${RED}FAILED!${NC}\n"
        inDir=$(basename $dir) 
        printf "+++++++++++++++++++++++++++++ Left: New | Right: Original | %s.c %s +++++++++++++++++++++++++++++\n" $inDir $flagName
        diff "diff_tmp.txt" $outName -y
        failed=$((failed+1))
    else 
        printf "${GREEN}PASSED!${NC}\n"
    fi
    total=$((total+1))
done

if [ "$failed" != "0" ]
then
    printf "${RED}$failed/$total FAILED!${NC}\n"
else 
    printf "${GREEN}$total/$total PASSED!${NC}\n"
fi

rm diff_tmp.txt