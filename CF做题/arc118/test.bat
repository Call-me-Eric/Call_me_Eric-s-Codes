:again
randdata
ARC118C < test.in > test.out
test < test.out > check.out
fc check.out tmp.out
if not errorlevel 1 goto again
pause