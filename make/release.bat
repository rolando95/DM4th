@echo off
g++    -Wall -O3 bin\*.o main.cpp -Iinclude -o main.exe  
IF %errorlevel%==0 (
    REM start main.exe
)