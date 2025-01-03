#!/bin/bash

n="2.c"
m="4.c"
echo "***************************"
echo "---------------------------"
gcc $n -o 2.out -lm
gcc $m -o 4.out -lm
cd ./tests
for ((i=1; i<=$(find . -maxdepth 1 -name "*.txt" | wc -l); i++))
do
    echo "testcase $i:"
    ../2.out < $i.txt > 2.$i.txt
    ../4.out < $i.txt > 4.$i.txt
    diff -w 2.$i.txt 4.$i.txt
    cat 2.$i.txt 
    cat 4.$i.txt
    rm 2.$i.txt 
    rm 4.$i.txt
    echo "---------------------------"
done
cd ..
rm 2.out
rm 4.out
echo "***************************"