#!/bin/sh

g++ -Wall -Wextra -o $1 $1.cpp
g++ -Wall -Wextra -o checker checker.cpp

for i in *.in; do
    echo $i
    ./$1 < $i > ${i%.in}.$1.out
    if ./checker $i ${i%.in}.$1.out; then
        score=$(./checker $i ${i%.in}.$1.out)
        mv ${i%.in}.$1.out sols/${i%.in}.${score% }.out
    fi
done;
