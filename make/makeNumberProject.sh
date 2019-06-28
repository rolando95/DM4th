g++   -Wall -O2 -c src/*.cpp
if [ $? -eq 0 ]; then
    mv *.o bin-int/release/x64

    g++ -g -Wall -c src/*.cpp
    if [ $? -eq 0 ]; then
        mv  *.o bin-int/debug/x64
    fi
fi