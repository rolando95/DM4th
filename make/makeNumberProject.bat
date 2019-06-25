@echo off
REM mkdir bin-int\release\x64\
REM mkdir bin-int\debug\x64\

g++   -Wall -O2 -c src\*.cpp
IF %errorlevel%==0 (
    move /Y *.o bin-int\release\x64 >nul

    g++ -g -Wall -Og -c src\*.cpp
    IF %errorlevel%==0 (
        move /Y *.o bin-int\debug\x64 >nul
    )
)