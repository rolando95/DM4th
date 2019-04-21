@echo off
g++    -Wall -O3 -c include\*.cpp
IF %errorlevel%==0 (
    move /Y *.o bin >nul

    g++ -g -Wall -Og -c include\*.cpp
    IF %errorlevel%==0 (
        move /Y *.o debug >nul
    )
)