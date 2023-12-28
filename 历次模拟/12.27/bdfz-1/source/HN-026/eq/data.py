from random import randint as rd
f=open("eq.in","w")
n,q,fl=rd(1,100),rd(1,100),rd(0,1)
#n,q,fl=700,700,0
f.write("%d %d\n"%(n,q))
a=[]
for i in range(n):
	a.append([])
	for j in range(n+1):
		a[-1].append(rd(0,998244352))
		f.write("%d "%a[-1][-1])
	f.write("\n")
for i in range(q):
	p=rd(0,n-1)
	f.write("%d "%(p+1))
	if rd(0,2)==0 and fl:
		x=rd(0,n-1)
		for j in range(n):
			a[p][j]=a[x][j]
			f.write("%d "%a[x][j])
		if rd(0,1):
			a[p][-1]=a[x][-1]
		else:
			a[p][-1]=rd(0,998244352)
		f.write("%d "%a[p][-1])
	else:
		a[p]=[]
		for j in range(n+1):
			a[p].append(rd(0,998244352))
			f.write("%d "%a[p][-1])
	f.write("\n")
