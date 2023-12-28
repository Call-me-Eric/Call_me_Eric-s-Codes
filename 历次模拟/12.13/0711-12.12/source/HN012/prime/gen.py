#!/bin/python3

from random import randint
from sys import argv

T=int(argv[1])
L=int(argv[2])

print(T)
for _ in range(T):
	l=randint(1,10**L-1)
	r=randint(1,10**L-1)
	if l>r:
		l,r=r,l
	print(l,r)
