#!/bin/python3

from random import randint, choice
from sys import argv

n=int(argv[1])
m=int(argv[2])
c=[0,0,0]
for _ in range(n-1):
	c[randint(0,2)]+=1
print(c[0],c[1],c[2],m)
e=set()
for i in range(m):
	while True:
		x=randint(1,n)
		y=randint(1,n)
		if x>y:
			x,y=y,x
		if (x,y) not in e:
			t=choice("rgb")
			e.add((x,y))
			print(x,y,t)
			break
