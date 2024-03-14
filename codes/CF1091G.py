from random import *
import math


def gcd(x, y):
    if y == 0:
        return x
    else:
        return gcd(y,x % y)


n = int(input())
val = []
ans = []
up = min(n,70)
for times in range(1,up):
    x = randint(1,n - 1)
    print("sqrt %d" % (x * x % n))
    y = int(input())
    if y == -1:
        continue
    if x != y:
        if x > y:
            x, y = y, x
        val.append(y - x)
        val.append(n // (y - x))
while n != 1:
    p = n
    for i in range(len(val)):
        if gcd(p,val[i]) != 1:
            p = gcd(p,val[i])
    for i in range(len(val)):
        if val[i] % p == 0:
            val[i] = val[i] // p
    while n % p == 0:
        n = n // p
    ans.append(p)
print("!", len(ans), *ans)
