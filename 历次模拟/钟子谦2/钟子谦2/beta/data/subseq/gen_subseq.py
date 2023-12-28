from cyaron import *
import random

# 生成20个测试数据
for i in range(1, 21):
    #选择对应于所需数据范围的n值和数值范围
    if i <= 2:
        n = 15
    elif i <= 6:
        n = 100
    elif i<=10:
        n = 2000
    elif i<=14:
        n=20000
    else:
        n=200000
    n-=random.randint(0,3)
    T=10
    test_in = IO(file_prefix="subseq", data_id=i)
    test_in.input_writeln(T)
    for _ in range(T):
        nn=random.randint(1,n)
        if _>1:
            nn=random.randint(n-n//10,n)
        def gen():
            a=0
            b=0
            c=0
            while random.randint(0,2)==0: a+=1
            while random.randint(0,1): b+=1
            while random.randint(0,2)==0: c+=1
            z=a+b*4+c*8
            return chr(z%26+ord('a'))
        test_in.input_writeln(''.join(gen()for _ in range(nn)))
    test_in.output_gen("subseq")