@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main
)

g++    -Wall -O2 %fileName%.cpp -Iinclude -o %fileName%.exe -fopenmp -DDM4thParallel

if errorlevel 1 ( exit /B 1 )

REM call bin\release\main.exe

exit /b 0