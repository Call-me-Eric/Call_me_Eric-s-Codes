#!/bin/python3

from sys import argv
from random import randint

MOD=998244353
n=int(argv[1])
q=int(argv[2])
print(n,q)
for i in range(n):
    for j in range(n+1):
        print(randint(0,MOD-1),end=' ')
    print()
for i in range(q):
    print(randint(1,n),end=' ')
    for i in range(n+1):
        print(randint(0,MOD-1),end=' ')
    print()
