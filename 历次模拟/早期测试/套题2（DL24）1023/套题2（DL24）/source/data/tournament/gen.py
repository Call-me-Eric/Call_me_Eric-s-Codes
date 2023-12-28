from random import *
from cyaron import *

num = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
n = [5, 5, 100, 100, 1000, 1000, 1000, 1000, 1000, 1000]
flag = [0, 0, 0, 0, 1, 1, 0, 0, 0, 0]

for i in range(10):
    io = IO(input_file='tournament' + str(num[i]) + '.in', output_file='tournament' + str(num[i]) + '.ans')
    if flag[i]:
        p = n[i] - randint(0, 50)
        io.input_writeln(p)
        for i in range(p):
            io.input_write(i + 1)
        io.input_writeln()
        io.output_gen('./test')
        continue
    nn = n[i] // 2 + 1
    if nn > 10:
        nn += randint(-15, -1)
    io.input_writeln(nn)
    b = list(range(1, n[i] + 1))
    shuffle(b)
    c = []
    for j in range(nn):
        c.append(b[j])
    c.sort()
    for i in range(nn):
        io.input_write(c[i])
        # io.input_write(' ')
    io.input_writeln()
    io.output_gen('./test')