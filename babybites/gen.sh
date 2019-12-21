#!/bin/bash

# Set the problem name to generate correct file names
PROBLEMNAME="babybites"
MAXN=1000

# Generating answers
cp submissions/accepted/torstein.py /tmp/sol.py
SOLVER=/tmp/sol.py

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

./generator.py -n 1 > $DR/01_n1_true.in
./generator.py -n 1 -f 1 > $DR/02_n1_false.in
./generator.py -n 1 -m 1 > $DR/03_n1_mumble.in
./generator.py -n 10 -m 0 -f 0 -o zeroindex > $DR/04_n10_m0_zeroindex.in

for i in {5..9}
do
    ./generator.py -s $i -n 9 -m $i -f 0 > $DR/0${i}_n9_m${i}_f0.in
done

for i in {0..9}
do
    ./generator.py -s 1${i} -n 10 -m $i -f 1 > $DR/1${i}_n10_m0_f${i}.in
done

for i in {0..4}
do
    ./generator.py -s 2${i} -n $MAXN -m $i -f 0 > $DR/2${i}_n${MAXN}_m${i}_f0.in
done

for i in {5..9}
do
    ./generator.py -s 2${i} -n $MAXN -m $i -f 1 > $DR/2${i}_n${MAXN}_m${i}_f1.in
done

./generator.py -s 30 -n $MAXN -m $MAXN -f 0 > $DR/30_n${MAXN}_m${MAXN}_f0.in


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
