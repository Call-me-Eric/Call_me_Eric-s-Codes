#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int ksm(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}
	return ans;
}
int x[705][705],a[705][705],v[705],n;
void solve()
{
	for(int i=1;i<=n;i++) for(int j=1;j<=n+1;j++) a[i][j]=x[i][j];
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		for(int j=i+1;j<=n;j++) if(a[j][i]>a[pos][i]) pos=j;
		for(int j=i;j<=n+1;j++) swap(a[pos][j],a[i][j]);
		if(a[i][i]==0) continue;
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			int div=1ll*a[j][i]*ksm(a[i][i],mod-2)%mod;
			for(int k=i;k<=n+1;k++) a[j][k]=(a[j][k]-1ll*a[i][k]*div%mod+mod)%mod;
		}
	}
	//for(int i=1;i<=n;i++)
	//{for(int j=1;j<=n+1;j++) printf("%d ",a[i][j]);puts("");}
	for(int i=1;i<=n;i++)
	{
		if(a[i][i]==0)
		{if(a[i][n+1]==0) puts("Many");else puts("No");return;}
		v[i]=1ll*a[i][n+1]*ksm(a[i][i],mod-2)%mod;
	}
	for(int i=1;i<=n;i++) printf("%d ",v[i]);
	puts("");
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	int q;cin>>n>>q;
	for(int i=1;i<=n;i++) for(int j=1;j<=n+1;j++) scanf("%d",&x[i][j]);
	solve();int pos;
	while(q--)
	{
		scanf("%d",&pos);
		for(int j=1;j<=n+1;j++) scanf("%d",&x[pos][j]);
		solve();
	}
	return 0;
}
