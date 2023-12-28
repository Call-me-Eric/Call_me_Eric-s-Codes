#include <bits/stdc++.h>
#define int long long
using namespace std;

int mod,t,l,r,a,sum[50000010],en=1;
int c[1800010];
void ad(int x,int v)
{
	for(int i=x+l*2;i<=4*(r-l+1)+l*2;i+=(i&-i))
	{
		c[i]+=v;
	}
}
int sus(int x)
{
	int res=0;
	for(int i=x+l*2;i;i-=(i&-i))
	{
		res+=c[i];
	}
	return res;
}
signed main()
{
	freopen("dark.in","r",stdin);
	freopen("dark.out","w",stdout);
	cin>>mod>>t;
	a=134775813%mod;
	if(a%4==0) sum[1]=-2;
	else if(a%2) sum[1]=1;
	for(int i=1;i<=t;i++)
	{
		cin>>l>>r;
		if(r>en)
		{
			for(int j=en+1;j<=r;j++)
			{
				a=(1103515245%mod*a%mod+1013904223%mod)%mod;
				if(a%4==0) sum[j]=sum[j-1]-2;
				else if(a%2) sum[j]=sum[j-1]+1;
				else sum[j]=sum[j-1];
			}
			en=r;
		}
		memset(c,0,sizeof(c));int ans=0;
		ad(sum[l-1],1);
		for(int j=l;j<=r;j++)
		{
			ans+=sus(sum[j]-1);ad(sum[j],1);
		}
		cout<<ans<<'\n';
	}
	return 0;
}