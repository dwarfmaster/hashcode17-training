#!/bin/sh

g++ -Wall -Wextra -o $1 $1.cpp
g++ -Wall -Wextra -o checker checker.cpp

for i in *.in; do
    echo $i
    ./$1 < $i > ${i%.in}.$1.out
    ./checker $i ${i%.in}.$1.out
done;
