:again
tmp > read.in
CF311D < read.in > out.out
Untitled-1 < read.in > ans.out
fc ans.out out.out
if not errorlevel 1 goto again
pause
