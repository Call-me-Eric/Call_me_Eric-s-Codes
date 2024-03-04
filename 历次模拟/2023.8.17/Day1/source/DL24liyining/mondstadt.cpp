#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e4+5,mod=1e9+7;
int cnt[maxn],chu[maxn],fac[maxn];

int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}

void init()
{
	fac[0]=1;
	for(int i=1;i<=maxn;i++) fac[i]=fac[i-1]*i%mod;
}

int C(int n,int m){return fac[n]*quickpow(fac[n-m]*fac[m]%mod,mod-2)%mod;}

signed main()
{
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;cin>>n>>m;
	init();
	for(int i=1;i<=m;++i)
	{
		int u,v;cin>>u>>v,chu[u]++,chu[v]++;
	}
	for(int i=2;i<n;++i)
		for(int j=1;j<=n;++j)
			if(chu[j]>=i) cnt[i]=(cnt[i]+C(chu[j],i))%mod;
	int ans=cnt[2];
	for(int i=3;i<n;++i) ans^=cnt[i];
	cout<<ans;
//	for(int i=2;i<n;i++) cout<<cnt[i]<<endl;
	return 0;
}

