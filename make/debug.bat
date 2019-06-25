REM @echo off
REM mkdir bin\debug\
g++ -g -Wall -Og bin-int\debug\x64\*.o main.cpp -Iinclude -o bin\debug\main.exe   
IF %errorlevel%==0 (
    REM start main.exe
)
