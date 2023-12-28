@echo off
:again
tmp > test.in
temp < test.in > ans.out
C_Ææ¹ÖÓÎÏ· < test.in > out.out
fc ans.out out.out
if not errorlevel 1 goto again
pause