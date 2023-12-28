g++ eq.cpp -o eq -O2
for ((i = 1; i <= 3; i++))
do
    time ./eq < eq$i.in > eq.out
    diff -w eq.out eq$i.ans
done