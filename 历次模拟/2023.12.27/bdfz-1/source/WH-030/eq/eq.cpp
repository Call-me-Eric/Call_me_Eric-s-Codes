#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long power(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		b/=2;
		a=a*a%mod;
	}
	return ans;
}
int n,q,z;
long long a[701][702],b[701][702];
void Gauss()
{
	int now=1;
	for(int i=1;i<=n;++i)
	{
		bool flag=1;
		for(int j=now;j<=n;++j)
			if(a[j][i])
			{
				for(int k=1;k<=n+1;++k)
					swap(a[now][k],a[j][k]);
				flag=0;
				break;
			}
		if(flag)continue;
		for(int j=1;j<=n;++j)
			if(j!=i&&a[j][i])
			{
				int t=power(a[now][i],mod-2)*a[j][i];
				for(int k=1;k<=n+1;++k)
					a[j][k]=(a[j][k]-t*a[now][k])%mod;
			}
		++now;
	}
	if(now==n+1)
	{
		for(int i=1;i<=n;++i)
			printf("%lld ",(power(a[i][i],mod-2)*a[i][n+1]%mod+mod)%mod);
		printf("\n");
		return;
	}
	for(int s=now;s<=n;++s)
		if(a[s][n+1])
		{
			printf("No\n");
			return;
		}
	printf("Many\n");
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout); 
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n+1;++j)
			scanf("%lld",&(a[i][j]));
	memcpy(b,a,sizeof b);
	Gauss(); 
	memcpy(a,b,sizeof a);
	for(int i=1;i<=q;++i)
	{
		scanf("%d",&z);
		for(int i=1;i<=n+1;++i)
			scanf("%lld",&(a[z][i]));
		memcpy(b,a,sizeof b);
		Gauss(); 
		memcpy(a,b,sizeof a);
	}
	return 0;
}
