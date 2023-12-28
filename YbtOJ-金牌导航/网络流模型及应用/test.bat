@echo off
:again
datamaker > test.in
ans < test.in > ans.out
G_ÅÚËş¹¥»÷ < test.in > out.out
fc out.out ans.out
if not errorlevel 1 goto again
pause