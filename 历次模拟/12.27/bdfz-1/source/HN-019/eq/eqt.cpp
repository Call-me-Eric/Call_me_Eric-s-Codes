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
	freopen("eq.out","w",stdout);
    int rt,x,d,ds,dt;
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
		if (qt==34)
		{
			for (int i=1;i<=n;++i)
			{
				for (int j=1;j<=n;++j) cerr<<(a[i][j]>0)<<' ';
				cerr<<endl;
			}
		}
		for (int i=1;i<=n+1;++i) c[i]=read();
		for (int i=n;i>=1;--i)
			if (b[i][x])
			{
				if (!rt) rt=i;
				else
				{
					d=1ll*b[i][x]*fast_pow(b[rt][x],mod-2)%mod;
					for (int j=1;j<=n+1;++j)
						if (a[rt][j])
							Adder2(a[i][j],-(long long)(a[rt][j])*d%mod);
					for (int j=1;j<=n;++j)
						if (b[rt][j])
							Adder2(b[i][j],-(long long)(b[rt][j])*d%mod);
				}
			}
		dt=0;
		for (int i=1;i<=n;++i)
			if (a[rt][i])
			{
				dt=i;
				break;
			}
		for (int i=1;i<=n+1;++i) Adder(a[rt][i],1ll*b[rt][x]*MD2(c[i]-st[x][i])%mod),st[x][i]=c[i];
		for (int i=1;i<=n;++i)
			if (i!=rt&&a[i][i]&&a[rt][i])
			{
				d=1ll*a[rt][i]*fast_pow(a[i][i],mod-2)%mod;
				for (int j=1;j<=n+1;++j)
					if (a[i][j])
						Adder2(a[rt][j],-(long long)(a[i][j])*d%mod);
				for (int j=1;j<=n;++j)
					if (b[i][j])
						Adder2(b[rt][j],-(long long)(b[i][j])*d%mod);
			}
		ds=0;
		for (int i=1;i<=n;++i)
			if (a[rt][i])
			{
				ds=i;
				break;
			}
		if (!ds)
		{
			for (int i=1;i<=n;++i)
				if (i!=rt&&a[i][rt])
					ds=i;
		}
		if (ds&&ds!=rt) swap(a[rt],a[ds]),swap(b[rt],b[ds]);
		for (int i=1;i<=n;++i)
			if (i!=rt&&a[i][rt]&&a[rt][rt])
			{
				d=(long long)(a[i][rt])*fast_pow(a[rt][rt],mod-2)%mod;
				for (int j=1;j<=n+1;++j)
					if (a[rt][j])
						Adder2(a[i][j],-(long long)(a[rt][j])*d%mod);
				for (int j=1;j<=n;++j)
					if (b[rt][j])
						Adder2(b[i][j],-(long long)(b[rt][j])*d%mod);
			}
		if (dt&&dt!=rt)
		{
			for (int i=1;i<=n;++i)
				if (i!=dt&&a[i][dt]&&a[dt][dt])
				{
					d=(long long)(a[i][dt])*fast_pow(a[dt][dt],mod-2)%mod;
					for (int j=1;j<=n+1;++j)
						if (a[dt][j])
							Adder2(a[i][j],-(long long)(a[dt][j])*d%mod);
					for (int j=1;j<=n;++j)
						if (b[dt][j])
							Adder2(b[i][j],-(long long)(b[dt][j])*d%mod);
				}
		}
		if (qt==34)
		{
			for (int i=1;i<=n;++i)
			{
				for (int j=1;j<=n;++j) cerr<<(a[i][j]>0)<<' ';
				cerr<<endl;
			}
		}
	   	get_ans();
	}
    return 0;
}
