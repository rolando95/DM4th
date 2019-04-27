@echo off
g++    -Wall -O2 bin\*.o main.cpp -Iinclude -o main.exe  
IF %errorlevel%==0 (
    REM start main.exe
)