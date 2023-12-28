from cyaron import *
import random

# 生成20个测试数据
for i in range(1, 21):
    #选择对应于所需数据范围的n值和数值范围
    if i <= 4:
        n = 100
    elif i <= 10:
        n = 2000
    else:
        n = 100000
    n-=random.randint(0,3)
    es = []
    if i>10 and i<=14:
        es = [(i,i+1) for i in range(1,n)]
    else:
        t = Graph.tree(n,chain=0.3,flower=0.1)
        es = []
        pm = list(range(n))
        random.shuffle(pm)
        for e in t.iterate_edges():
            x,y=e.start,e.end
            x=pm[x-1]+1
            y=pm[y-1]+1
            es.append((x,y))

    test_in = IO(file_prefix="meet", data_id=i)
    test_in.input_writeln(n)
    assert len(es)==n-1
    for a,b in es:
        assert 1<=a<=n>=b>=1
        test_in.input_writeln(a,b,random.randint(1,10**6))
    test_in.output_gen("meet")