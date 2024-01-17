#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=500010;
int n,a[N],b[N],mod=998244353;
int cnt[N],sum,vis[N];
int ans,num;
signed main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		cnt[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
		cnt[b[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>=1) sum++;
	}
	if(sum==n){
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			if(a[i]==b[i]) vis[a[i]]=1;
		} 
		ans=n;
		for(int i=2;i<=n;i++)
		{
			ans=ans*n%mod;
		}
		for(int i=1;i<=n;i++)
		{
			if(vis[i]!=1)
			{
				num=1;
				for(int j=1;j<=n-cnt[a[i]];j++)
				{
					num=num*n%mod;
				}
				ans-=num;
				//vis[a[i]]=1;
			}
		}
		printf("%lld",ans);
	}
	else{
		ans=n;
		for(int i=2;i<=n;i++)
		{
			ans=ans*n%mod; 
		}
		printf("%lld",ans); 
	}
	return 0;
}
