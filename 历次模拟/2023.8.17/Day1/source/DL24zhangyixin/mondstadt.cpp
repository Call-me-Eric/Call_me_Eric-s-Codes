#include<bits/stdc++.h>
using namespace std;
const int N=405;
int n,m,u,v,mod=1e9+7;
int a[N],cnt[N],maxn=-1,b[N],f[N][N];
int sum=1;
int main()
{
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&u,&v);
		if(f[u][v]!=1&&f[v][u]!=1)
		{
			a[u]++;
			a[v]++;
			f[u][v]=1;
			f[v][u]=1;
		}
	}
	b[1]=1;
	for(int i=2;i<=m;i++)
	{
		b[i]=b[i-1]+i;
	}
	for(int i=1;i<=n;i++)
	{
		maxn=max(maxn,a[i]);
		sum=1;
		if(a[i]==1)continue;
		for(int j=a[i];j>=2;j--)
		{
			cnt[j]+=b[sum];
			sum++;
		}
	}
	int ans=0;
	for(int i=1;i<=maxn;i++)
	{
		ans=ans^cnt[i]%mod;
	}
	printf("%d",ans);
	return 0;
}
