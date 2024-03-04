#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int mod=1e9+7;
int n,m,maxx,ans;
int cnt[N],out[N];
int fac[N],ifac[N],cnt1[N];
int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
		{
			res*=x;
			res%=mod;
		}
		x*=x;
		x%=mod;
		y>>=1;
	}
	return res;
}
void pre()
{
	fac[0]=1;
	ifac[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i;
		ifac[i]=ksm(fac[i],mod-2);
	}
}
int c(int x,int y)
{
	return (fac[x]*ifac[x-y]%mod)*ifac[y]%mod;
}
signed main()
{
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	cin>>n>>m;
	pre();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		out[x]++;
		out[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		cnt[out[i]]++;
		cnt[out[i]]%=mod;
	}
	for(int i=2;i<=n-1;i++)
	{
		if(cnt[i]==0)continue;
		for(int j=2;j<=i;j++)
		{
			cnt1[j]+=cnt[i]*c(i,j);
		}
	}
	for(int i=2;i<=n-1;i++)
	{
		ans^=cnt1[i];
	}
	cout<<ans;
}
