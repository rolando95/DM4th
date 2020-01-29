#!/bin/sh

search_dir=$PWD

echo "\n-------------------- NO PARALLEL --------------------\n"

for file in "$search_dir"/*/*.cpp 
do
    echo "\n----- $file -----\n"
    g++ $file -o test -ggdb3 -mavx2 -Wall -std=c++11 -pedantic -D DM4thOnlyStandardLiterals -fopenmp
    if [ $? -ne 0 ]; then exit 1; fi

    if [ "$1" = "usevalgrind" ]
    then
        valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./test
    else
        ./test
    fi
    if [ $? -ne 0 ]; then exit 1; fi
done

echo "\n-------------------- PARALLEL --------------------\n"

for file in "$search_dir"/*/*.cpp
do
    echo "\n----- $file -----\n"
    g++ $file -o test -ggdb3 -Wall -std=c++11 -pedantic -D DM4thOnlyStandardLiterals -D DM4thAutoParallel -D DM4thMinParallelLoops=1 -fopenmp
    if [ $? -ne 0 ]; then exit 1; fi

    if [ "$1" = "usevalgrind" ]
    then
        valgrind  --show-leak-kinds=all --error-exitcode=1  --show-possibly-lost=no ./test
    else
        ./test
    fi
    if [ $? -ne 0 ]; then exit 1; fi
donesearch_dir=$PWD

echo "\n-------------------- NO PARALLEL --------------------\n"

for file in "$search_dir"/*/*.cpp 
do
    echo "\n----- $file -----\n"
    g++ $file -o test -ggdb3 -mavx2 -Wall -std=c++11 -pedantic -D DM4thOnlyStandardLiterals -fopenmp
    if [ $? -ne 0 ]; then exit 1; fi

    if [ "$1" = "usevalgrind" ]
    then
        valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./test
    else
        ./test
    fi
    if [ $? -ne 0 ]; then exit 1; fi
done

echo "\n-------------------- PARALLEL --------------------\n"

for file in "$search_dir"/*/*.cpp
do
    echo "\n----- $file -----\n"
    g++ $file -o test -ggdb3 -Wall -std=c++11 -pedantic -D DM4thOnlyStandardLiterals -D DM4thAutoParallel -D DM4thMinParallelLoops=1 -fopenmp
    if [ $? -ne 0 ]; then exit 1; fi

    if [ "$1" = "usevalgrind" ]
    then
        valgrind  --show-leak-kinds=all --error-exitcode=1  --show-possibly-lost=no ./test
    else
        ./test
    fi
    if [ $? -ne 0 ]; then exit 1; fi
done