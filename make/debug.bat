@echo off
g++ -g -Wall -Og debug\*.o main.cpp -Iinclude -o debug\main.exe   
IF %errorlevel%==0 (
    REM start main.exe
)
