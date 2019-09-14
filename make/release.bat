@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main.cpp
)

if not exist bin\release\ mkdir bin\release\
g++    -Wall -O2 bin-int\release\x64\*.o %fileName% -Iinclude -o bin\release\main.exe  

if errorlevel 1 ( exit /B 1 )

REM call bin\release\main.exe

exit /b 0