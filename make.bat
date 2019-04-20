@echo off
DEL bin\*.o
g++ -Wall -O3 -c include\*.cpp
IF %errorlevel%==0 (
    move *.o bin >nul
)
IF %errorlevel%==0 (
    g++ -Wall bin\*.o main.cpp -Iinclude -o main.exe   
)
IF %errorlevel%==0 (
    REM start main.exe
    main.exe
)