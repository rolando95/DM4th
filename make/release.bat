REM @echo off
REM mkdir bin\release\
g++    -Wall -O2 bin-int\release\x64\*.o main.cpp -Iinclude -o bin\release\main.exe  
IF %errorlevel%==0 (
    REM start main.exe
)