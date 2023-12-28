s=rgb
g++ $s.cpp -o $s -std=c++14 -O2
g++ bf.cpp -o bf -std=c++17 -O2
g++ dt.cpp -o dt -std=c++17 -O2
for ((i = 1; ; i++))
do
    ./dt < rg > dt.in
    ./$s < dt.in > $s.out
    ./bf < dt.in > bf.out
    if diff -w $s.out bf.out; then
        echo $i
    else
        break
    fi
done