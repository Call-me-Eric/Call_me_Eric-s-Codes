#include<bits/stdc++.h>
using namespace std;
int n,k;
long long ans=0,dp[1005][1005],mod=1e9+7;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(i==1&&j==1) dp[i][j]=k;
			else
			dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]*(k-(j-1)))%mod;
		}
	}
	for(int i=1;i<=k;i++)
	{
		ans=(ans+dp[n][i])%mod;
	}
	printf("%lld",ans%mod);
	return 0;
}
