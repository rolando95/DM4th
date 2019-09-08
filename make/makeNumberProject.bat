@echo off
cd ../
echo %cd%

set OUTPUT_RELEASE=bin-int\release\x64\
set OUTPUT_DEBUG=bin-int\debug\x64\
if not exist %OUTPUT_RELEASE% mkdir %OUTPUT_RELEASE%
if not exist %OUTPUT_DEBUG% mkdir %OUTPUT_DEBUG%

g++   -Wall -O2 -c src\*.cpp

if errorlevel 1 ( exit /B 1 )

move /Y *.o bin-int\release\x64 >nul

if errorlevel 1 ( exit /B 1 )

g++ -g -Wall -Og -c src\*.cpp

if errorlevel 1 ( exit /B 1 )

move /Y *.o bin-int\debug\x64 >nul

exit /b %errorlevel%