@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main.cpp
)

if not exist bin\debug\ mkdir bin\debug\
g++ -ggdb -Wall bin-int\debug\x64\*.o %fileName% -Iinclude -o bin\debug\main.exe 

if errorlevel 1 ( exit /B 1 )

REM call bin\debug\main.exe

exit /b 0