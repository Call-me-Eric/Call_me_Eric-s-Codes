#include<iostream>
#include<cstdio>
#define N 701
#define mod 998244353
using namespace std;
int read()
{
	char c=0;
	int sum=0;
	while (c<'0'||c>'9') c=getchar();
	while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
	return sum;
}
void Adder(int &x,int d)
{
	x+=d;
	if (x>=mod) x-=mod;
	return;
}
void Adder2(int &x,int d)
{
	x+=d;
	if (x<0) x+=mod;
	return;
}
int MD(int x)
{
	return x>=mod?x-mod:x;
}
int MD2(int x)
{
	return x<0?x+mod:x;
}
int fast_pow(int a,int b)
{
	int res=1,mul=a;
	while (b)
	{
		if (b&1) res=1ll*res*mul%mod;
		mul=1ll*mul*mul%mod,b>>=1;
	}
	return res;
}
int n,q,st[N+1][N+1],a[N+1][N+1],b[N+1][N+1],c[N+1];
void gauss()
{
	int d;
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=n;++j)
			if (!a[i][i]&&a[j][i]&&(j>i||!a[j][j]))
				swap(a[i],a[j]),swap(b[i],b[j]);
		if (a[i][i])
		{
			for (int j=1;j<=n;++j)
				if (j!=i&&a[j][i])
				{
					d=(long long)(a[j][i])*fast_pow(a[i][i],mod-2)%mod;
					for (int k=1;k<=n+1;++k)
						if (a[i][k])
							Adder2(a[j][k],-(long long)(a[i][k])*d%mod);
					for (int k=1;k<=n;++k)
						if (b[i][k])
							Adder2(b[j][k],-(long long)(b[i][k])*d%mod);
				}
		}
	}
	return;
}
void get_ans()
{
	bool op=0;
	for (int i=1;i<=n;++i)
		if (!a[i][i])
			op=1;
	if (op)
	{
		for (int i=1;i<=n;++i)
			if (!a[i][i]&&a[i][n+1])
			{
				puts("No");
				return;
			}
		puts("Many");
	}
	else
	{
		for (int i=1;i<=n;++i) printf("%lld ",(long long)(a[i][n+1])*fast_pow(a[i][i],mod-2)%mod);
		puts("");
	}
	return;
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.ans","w",stdout);
    int rt,x,d,ds;
	n=read(),q=read();
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=n+1;++j) a[i][j]=st[i][j]=read();
		b[i][i]=1;
	}
	gauss(),get_ans();
	while (q--)
	{
		x=read(),rt=0;
		for (int i=1;i<=n+1;++i) st[x][i]=read();
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n+1;++j)
				a[i][j]=st[i][j];
		gauss(),get_ans();
	}
    return 0;
}
