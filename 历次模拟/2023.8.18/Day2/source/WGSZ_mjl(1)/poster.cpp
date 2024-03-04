#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<30),mod=998244353;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
inline int ksm(int x,int y,const int mod)
{
	int ks=1;
	for(;y;x=x*x%mod,y>>=1)if(y&1)ks=ks*x%mod;
	return ks;
}
inline int ksc(int x,int y,const int mod)
{
	int ks=0;
	for(;y;x=(x+x)%mod,y>>=1)if(y&1)ks=(ks+x)%mod;
	return ks;
}
int n,m,T,ans;
int a[N];
inline int num()
{
	int sum=0;
	for(int i=1;i<=n;i++)if(a[i]!=i)sum++;
	return sum;
}
int p1;
inline void dfs(int x,int sum)
{
	if(x==m+1)
	{
		ans=(ans+sum*num()*p1%mod)%mod;
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			swap(a[i],a[j]);
			if(i==j)dfs(x+1,sum);
			else dfs(x+1,sum*2);
			swap(a[i],a[j]);
		}
	}
}
signed main()
{
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	T=read();
	while(T--)
	{
		ans=0;
		n=read();m=read();
		p1=ksm(ksm(n,2,mod),mod-2,mod);
		p1=ksm(p1,m,mod);
		for(int i=1;i<=n;i++)a[i]=i;
		dfs(1,1);
		printf("%lld\n",ans);
	}
	return 0;
}
/*
3
1 0
1 1
2 1

		for(int i=1;i<=n;i++)//换走i个信的概率 好像不能这样算，它  
		{
			ans=(ans+ksm(x1,i,mod)*ksm(x2,n-i,mod)%mod)%mod;
		}
*/
