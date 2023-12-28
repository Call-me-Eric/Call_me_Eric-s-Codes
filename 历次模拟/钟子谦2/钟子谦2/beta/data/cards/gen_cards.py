from cyaron import *
import random

# 对于所有数据，1≤n≤5000，0≤ai,bi≤10^9
# 对于 10% 的数据，n≤20。
# 对于 30% 的数据，n≤50，ai,bi≤50。
# 对于 50% 的数据，n≤50。
# 对于 70% 的数据，n≤400。

# 定义不同的n值，包含全部所需要的n
ns=[20, 50, 50, 400, 5000]

# 定义不同的数值范围
ranges=[[0, 50], [0, 10**9]]

# 生成20个测试数据
for i in range(1, 21):
    #选择对应于所需数据范围的n值和数值范围
    if i <= 2:   #10% 
        n = ns[0]
    elif i <= 10: #50%
        n = ns[1]
    elif i <= 14:#70%
        n = ns[3]
    else:
        n = ns[4]

    r = ranges[0] if i <= 6 else ranges[1]

    # 生成输入文件
    test_in = IO(file_prefix="cards", data_id=i)
    test_in.input_writeln(n)
    for _ in range(0, n):
        R = r[1]
        while random.random()<0.8: R//=2
        ai = random.randint(r[0], R)
        R = r[1]
        while random.random()<0.6: R//=2
        bi = random.randint(r[0], R)
        test_in.input_writeln(ai, bi)

    test_in.output_gen("cards")