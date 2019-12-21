#!/usr/bin/env bash

g++ -Wall -O3 -std=c++11 ../submissions/accepted/dp_faster.cpp -o sol

CASE=0
function gen {
    CASE=$(( CASE + 1 ))
    echo $CASE
    python ./random_generator.py $CASE $1 $2 $3 $4 $5 > ../data/secret/$(printf "%03d" $CASE).in
    time ./sol < ../data/secret/$(printf "%03d" $CASE).in > ../data/secret/$(printf "%03d" $CASE).ans
}

# n = int(sys.argv[2])
# sparseness = float(sys.argv[3])
# max_weight = int(sys.argv[4])
# qs = int(sys.argv[5])
# max_time = int(sys.argv[6])

# for p in 0 2 4 6 8; do
#     gen 10 0.$p 8   2 10
#     gen 10 0.$p 8   5 50
#     gen 10 0.$p 8  10 80
# done

rm ../data/secret/*

for p in 0 2 4 6 8; do
    for t in 80000 40000 10000 1000 100; do
        gen 100 0.$p 8 100 $t 
    done
done

for p in 0 2 4; do
    for t in 10000000 1000000 100000 10000; do
        gen 1000 0.000$p 8 1000 $t
    done
done

for p in 1 2 4; do
    for t in 50000000 10000000 1000000 100000; do
        gen 1000 0.000$p 20 1000 $t
    done
done

for p in 0 2 4; do
    for t in 100000000 50000000 10000000 1000000; do
        gen 1000 0.000$p 1000 1000 $t
    done
done

for p in 0 1 3; do
    for t in 100000000 50000000 10000000; do
        gen 1000 0.000$p 10000 1000 $t
    done
done

rm ./sol

