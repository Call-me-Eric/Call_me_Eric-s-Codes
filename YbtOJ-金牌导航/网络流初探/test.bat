@echo off
:again
tmp > test.in
temp < test.in > ans.out
C_�����Ϸ < test.in > out.out
fc ans.out out.out
if not errorlevel 1 goto again
pause