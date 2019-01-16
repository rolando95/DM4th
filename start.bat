@echo off
DEL bin\*.o
g++ -w -c include\*.cpp
move *.o bin
IF %errorlevel%==0 (
    g++ -w bin\*.o main.cpp -Iinclude -o main.exe   
)

IF %errorlevel%==0 (
    REM cls
    main.exe
)

REM xcopy c:\example c:\example2