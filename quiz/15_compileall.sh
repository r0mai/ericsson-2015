#!/bin/bash

for i in $(seq 0 64); do
    file="15_generated_${i}.cpp"
    clang++ -std=c++14 ${file} > /dev/null 2>&1
    ./a.out
done
