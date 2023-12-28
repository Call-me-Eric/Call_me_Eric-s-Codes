:again
@REM datamaker > test.in
CF1684F-ans < test.in > ans.out
CF1684F < test.in > out.out
fc out.out ans.out
if not errorlevel 1 goto again
pause