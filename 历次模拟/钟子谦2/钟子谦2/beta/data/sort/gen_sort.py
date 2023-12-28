from cyaron import *
import random

# 生成20个测试数据
for i in range(1, 21):
    #选择对应于所需数据范围的n值和数值范围
    n = 500000
    rd = 0
    if i <= 2:
        n = 500
    elif i <= 8:
        n = 4000
    elif i<=14:
        rd = 1
    if rd == 0 and i%3==0:
        rd = 1
    t=[0]*n
    if rd:
        t=list(range(n))
        random.shuffle(t)
    else:
        S = int(n**0.7)
        print(n,'!')
        cp = 0
        for w in range(S):
            gg = list(range(cp,cp+len(range(w,n,S))))
            random.shuffle(gg)
            cp+=len(gg)
            for ii in range(w,n,S):
                t[ii]=gg.pop()
        assert cp==n
    test_in = IO(file_prefix="sort", data_id=i)
    test_in.input_writeln(n)
    test_in.input_writeln([_+1 for _ in t])
    print(i,rd)
    test_in.output_gen("sort.exe")