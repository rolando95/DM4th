@echo off
g++ -w bin\*.o main.cpp -Iinclude -o main.exe   
IF %errorlevel%==0 (
    main.exe
)