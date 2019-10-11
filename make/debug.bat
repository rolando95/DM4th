@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main
)

g++ -std=c++11 -ggdb -Wall  %fileName%.cpp -o %fileName%.exe

if errorlevel 1 ( exit /B 1 )

REM call bin\debug\main.exe

exit /b 0