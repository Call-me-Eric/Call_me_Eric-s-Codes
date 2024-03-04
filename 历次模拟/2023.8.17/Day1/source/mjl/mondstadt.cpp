#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
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
int n,m,du[N],ans;
struct no
{
	int du,num;
}num[N];
inline bool cmp(const no &aa,const no &bb){return (aa.num&&bb.num)?aa.du>bb.du:aa.num>bb.num;}
int fac[N],inv[N];
inline void pre()
{
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
//inline int C(const int n,const int m){return (m>=n)?fac[m]*inv[m-n]%mod*inv[n]%mod:0;}
inline int C(const int n,const int m){return fac[m]*inv[m-n]%mod*inv[n]%mod;}
signed main()
{
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	n=read();m=read();
	pre();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		du[x]++;du[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		num[i].du=i;
		num[du[i]].num++;
	}
	sort(num+1,num+1+n,cmp);
	for(int k=2;k<n;k++)
	{
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			if(!num[i].num||num[i].du<k)break;
			sum=(sum+num[i].num*C(k,num[i].du)%mod)%mod;
		}
		ans^=sum;
	}
	cout<<ans;
	return 0;
}
/*

*/
