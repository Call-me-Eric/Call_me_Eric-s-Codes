s="ur"
g++ -o a $s.cpp -fsanitize=address,undefined
time ./a