#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline int read()
{
	int res=0,op=0;
	char ch=getchar();
	while(!isdigit(ch))
	{
		op|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	return op?-res:res;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10^48);
}
const int mod=998244353;
inline ll qpow(ll x,int y)
{
	ll res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return res;
}
int n,q,a,b;
inline void print()
{
	if(!b)
	{
		if(!a) puts("Many");
		else puts("0");
		return;
	}
	if(!a)
	{
		puts("No");
		return;
	}
	write(b*qpow(a,mod-2)%mod);
	puts("");
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read();
	q=read();
	a=read();
	b=read();
	print();
	while(q--)
	{
		int op=read();
		a=read();
		b=read();
		print();
	}
	return 0;
}
