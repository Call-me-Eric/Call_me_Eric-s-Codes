import random
import os
import math

name="eliminate"

def mkd(filename, n):
    file=open(filename, "w")
    
    for i in range(n-1):
        file.write(f"{random.choice(['R','G','B'])} ")
    file.write(f"{random.choice(['R','G','B'])}\n")
    file.close()

os.system(f"g++ {name}.cpp -o {name}.exe -O2 -lm")

for i in range(1,21):
    print(i)
    n = 10**7
    if i<=14:
        n = 10**3
    if i<=8:
        n = 10
    mkd(f'{name}.in', n)
    os.system(f'{name}.exe')
    os.system(f'move {name}.in {name}{i}.in')
    os.system(f'move {name}.out {name}{i}.out')
        