@echo off
cd ../
echo %cd%

mkdir bin\release\
g++    -Wall -O2 bin-int\release\x64\*.o main.cpp -Iinclude -o bin\release\main.exe  

if errorlevel 1 ( exit /B 1 )

REM call bin\release\main.exe

exit /b 0