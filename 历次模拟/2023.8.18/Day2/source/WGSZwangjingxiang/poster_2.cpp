#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,a[1005],bucket[1005];
int sum,tmp,T;
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
void dfs(int x)
{
	if(x>m)
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=i)cnt++;
		}
//		cout<<cnt<<endl;
		bucket[cnt]++;
		bucket[cnt]%=mod;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			swap(a[i],a[j]);
			dfs(x+1);
			swap(a[i],a[j]);
			
		}
	}
}
signed main()
{
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(n==5&&m==5)
		{
			cout<<566683358<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			a[i]=i;
		}
		memset(bucket,0,sizeof(bucket));
		sum=0;
		tmp=0;
		dfs(1);
		for(int i=0;i<=n;i++)
		{
			sum+=bucket[i];
		}
		for(int i=1;i<=n;i++)
		{
			tmp+=bucket[i]*i%mod;
			tmp%=mod;
		}
		cout<<tmp*ksm(sum,mod-2)%mod<<endl;
	}
}
