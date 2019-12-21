#!/usr/bin/env bash

python gendata.py

for f in secret/*.in; do
    python ../submissions/accepted/bjarki.py < $f > ${f%.in}.ans
done

