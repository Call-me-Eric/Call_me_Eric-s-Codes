@echo off
:again
datamaker
tmp
alphadog
fc alphadog.out alphadog.ans
if not errorlevel 1 goto again
pause