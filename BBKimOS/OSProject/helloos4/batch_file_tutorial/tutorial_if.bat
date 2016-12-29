@echo off

set /p input_page=input program name :

if "%c%"=="notepad" notepad
if "%c%"=="calc" calc

if "%c%"== "google" explorer "http://www.google.com"

pause > nul
