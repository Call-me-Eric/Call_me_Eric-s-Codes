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
int n,q,st[N+1][N+1],a[N+1][N+1],b[N+1][N+1],c[N+1],sx[N+1];
void gauss()
{
	int d;
	for (int i=1;i<=n;++i)
	{
		for (int j=i+1;j<=n;++j)
			if (!a[i][i]&&a[j][i])
				swap(a[i],a[j]),swap(b[i],b[j]);
		if (a[i][i])
		{
			for (int j=i+1;j<=n;++j)
				if (a[j][i])
				{
					d=1ll*a[j][i]*fast_pow(a[i][i],mod-2)%mod;
					for (int k=i;k<=n+1;++k)
						if (a[i][k])
							Adder2(a[j][k],-1ll*a[i][k]*d%mod);
					for (int k=1;k<=n;++k)
						if (b[i][k])
							Adder2(b[j][k],-1ll*b[i][k]*d%mod);
				}
		}
	}
	return;
}
void get_ans()
{
	for (int i=n;i>=1;--i)
	{
		sx[i]=a[i][n+1];
		for (int j=i+1;j<=n;++j)
			if (a[i][j])
			{
				if (sx[j]==-1)
				{
					sx[i]=-1;
					break;
				}
				Adder2(sx[i],-1ll*sx[j]*a[i][j]%mod);
			}
		if (sx[i]>0&&!a[i][i])
		{
			puts("No");
			return;
		}
		if (sx[i]==0&&!a[i][i]) sx[i]=-1;
		if (a[i][i]) sx[i]=1ll*sx[i]*fast_pow(a[i][i],mod-2)%mod;
	}
	for (int i=1;i<=n;++i)
		if (sx[i]==-1)
		{
			puts("Many");
			return;
		}
	for (int i=1;i<=n;++i) printf("%d ",sx[i]);
	puts("");
	return;
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
    int rt,x,d;
	n=read(),q=read();
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=n+1;++j) a[i][j]=st[i][j]=read();
		b[i][i]=1;
	}
	gauss(),get_ans();
	for (int qt=1;qt<=q;++qt)
	{
		x=read(),rt=0;
		for (int i=1;i<=n+1;++i) c[i]=read();
		for (int i=n;i>=1;--i)
			if (b[i][x])
			{
				if (!rt) rt=i;
				else
				{
					d=1ll*b[i][x]*fast_pow(b[rt][x],mod-2)%mod;
					for (int j=rt;j<=n+1;++j)
						if (a[rt][j])
							Adder2(a[i][j],-1ll*a[rt][j]*d%mod);
					for (int j=1;j<=n;++j)
						if (b[rt][j])
							Adder2(b[i][j],-1ll*b[rt][j]*d%mod);
				}
			}
		for (int i=1;i<=n+1;++i) Adder(a[rt][i],1ll*b[rt][x]*MD2(c[i]-st[x][i])%mod),st[x][i]=c[i];
		for (int i=1;i<=rt-1;++i)
			if (a[rt][i])
			{
				if (!a[i][i]) swap(a[i],a[rt]),swap(b[i],b[rt]);
				else
				{
					d=1ll*a[rt][i]*fast_pow(a[i][i],mod-2)%mod;
					for (int j=i;j<=n+1;++j)
						if (a[i][j])
							Adder2(a[rt][j],-1ll*a[i][j]*d%mod);
					for (int j=1;j<=n;++j)
						if (b[i][j])
							Adder2(b[rt][j],-1ll*b[i][j]*d%mod);
				}
			}
	   	get_ans();
	}
    return 0;
}
