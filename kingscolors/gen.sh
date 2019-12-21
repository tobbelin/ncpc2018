#!/bin/bash

# Set the problem name to generate correct file names
PROBLEMNAME="landoftrees"
MAXN=2500

# Generating answers
cp submissions/accepted/per.py /tmp/sol.py
SOLVER=/tmp/sol.py
chmod +x $SOLVER

subfolders=(data/secret)
for i in ${subfolders[@]}
do
    rm -r $i
    if [ ! -d $i ]
    then
        mkdir $i
    fi
done


echo "Generating..."
DR="data/secret"

./generator.py -s 1 -n 2 > $DR/01_tiny_n_equals_two.in
./generator.py -s 2 -n 5 -k 5 > $DR/02_tiny_k_equals_n.in
./generator.py -s 3 -n 5 -k 2 > $DR/03_tiny_k_equals_two.in
./generator.py -s 4 -n 5 -k 3 > $DR/04_tiny_random.in

./generator.py -s 5 -n $MAXN -k $MAXN > $DR/05_big_k_equals_n.in
./generator.py -s 6 -n $MAXN -k 2 > $DR/06_big_k_equals_two.in
./generator.py -s 7 -n $MAXN -k 3 > $DR/07_big_k_equals_three.in
./generator.py -s 8 -n $MAXN -o random > $DR/08_big_random.in
./generator.py -s 9 -n $MAXN -o balanced > $DR/09_big_balanced.in
./generator.py -s 10 -n $MAXN -o onepath > $DR/10_big_onepath.in
./generator.py -s 11 -n $MAXN -o twopaths > $DR/11_big_twopath.in


# generate solutions for all files
if [[ ! -z $SOLVER ]]
then
    for i in ${subfolders[@]}
    do
        for f in $i/*.in
        do
            echo "solving $f"
            $SOLVER < $f > ${f%???}.ans
        done
    done
fi
