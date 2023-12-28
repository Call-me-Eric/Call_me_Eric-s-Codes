echo off
:again
tmp > test.in
CF1031C < test.in > tmp.out
check < tmp.out > test.out
fc test.in test.out
if not errorlevel 1 goto again
pause