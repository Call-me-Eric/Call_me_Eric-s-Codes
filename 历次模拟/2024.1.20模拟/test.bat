@echo off
:again
datamaker
dudu
fc fail.out dudu.out
if errorlevel 1 goto again
pause
