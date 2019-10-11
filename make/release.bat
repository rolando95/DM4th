@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main
)

g++  -std=c++11 -Wall -O2 %fileName%.cpp -o %fileName%.exe -fopenmp -D DM4thParallel

if errorlevel 1 ( exit /B 1 )

REM call bin\release\main.exe

exit /b 0