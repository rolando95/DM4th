@echo off
cd ../

set fileName=%1
if "%fileName%"=="" (
    set fileName=main.cpp
)
mkdir bin\debug\
g++ -ggdb -Wall bin-int\debug\x64\*.o %fileName% -Iinclude -o bin\debug\main.exe  
IF %errorlevel%==0 (
    cls
    REM start main.exe
)
