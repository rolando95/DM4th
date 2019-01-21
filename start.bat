@echo off
DEL bin\*.o
g++ -w -c include\*.cpp
move *.o bin >nul
IF %errorlevel%==0 (
    g++ -w bin\*.o main.cpp -Iinclude -o main.exe   
)
IF %errorlevel%==0 (
    main.exe
)