@echo off
g++    -Wall -O2 -c include\_Number\*.cpp
IF %errorlevel%==0 (
    move /Y *.o bin >nul

    g++ -g -Wall -Og -c include\_Number\*.cpp
    IF %errorlevel%==0 (
        move /Y *.o debug >nul
    )
)