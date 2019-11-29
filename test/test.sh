search_dir=$PWD

echo "\n-------------------- NO PARALLEL --------------------\n"

for file in "$search_dir"/*/*.cpp
do
    echo "\n----- $file -----\n"
    g++ $file -o test -ggdb3 -std=c++11 -D DM4thOnlyStandardLiterals
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
    g++ $file -o test -ggdb3 -std=c++11 -D DM4thOnlyStandardLiterals -D DM4thParallel -D DM4thMinOmpLoops=1 -fopenmp
    if [ $? -ne 0 ]; then exit 1; fi

    ./test
    if [ $? -ne 0 ]; then exit 1; fi
done