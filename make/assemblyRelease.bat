@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main
)

g++    -Wall -O2 %fileName%.cpp -Iinclude -S -o %fileName%.asm 

if errorlevel 1 ( exit /B 1 )

REM call bin\release\main.exe

exit /b 0