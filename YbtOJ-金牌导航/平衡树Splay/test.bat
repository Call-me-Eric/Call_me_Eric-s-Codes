:again
@REM datamaker
F_ά������ < in.in > out.out
ans < in.in > ans.out
fc ans.out out.out
if not errorlevel 1 goto again
pause
