@echo off
cls
g++ *.cpp -o main
if %errorlevel% equ 0 (
    main.exe
) else (
    echo Compilation failed.
)