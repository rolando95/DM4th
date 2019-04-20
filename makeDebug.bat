@echo off
DEL bin\*.o
g++ -g -Wall -Og -c include\*.cpp
IF %errorlevel%==0 (
    move *.o bin >nul
)
IF %errorlevel%==0 (
    g++ -g -Wall -Og bin\*.o main.cpp -Iinclude -o main.exe   
)
IF %errorlevel%==0 (
    REM start main.exe
    REM main.exe
)