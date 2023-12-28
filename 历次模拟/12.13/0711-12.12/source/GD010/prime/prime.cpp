#include<bits/stdc++.h>
#define int long long
using namespace std;
int MOD=998244353;
vector<int> an;
int pr[30]={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
int nt[15][30];
void dfs(int nx,int ns,int nk=0)
{
	if(nx==1000000000)
	{
		an.push_back(ns);
		return;
	}
	for(int i=0;i<10;i++)
	{
		bool ok=1;
		for(int j=0;pr[j];j++)
		{
			if(nt[nk][j]%10==i)	nt[nk+1][j]=nt[nk][j]/10;
			else				nt[nk+1][j]=nt[nk][j];
			if(!nt[nk+1][j])	ok=0;
		}
		if(!ok)	continue;
		dfs(nx*10,ns+i*nx,nk+1);
	}
}
char c[100005];
int ans[100005];
signed main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	for(int i=0;pr[i];i++)	nt[0][i]=pr[i];
	dfs(1,0);
	cout<<'!'<<'\n';
	int T;
	scanf("%lld",&T);
	an.push_back(1000000000);
	sort(an.begin(),an.end());
	while(T--)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		int ans=0;
		ans=upper_bound(an.begin(),an.end(),y)-upper_bound(an.begin(),an.end(),x-1);
		cout<<ans<<'\n';
	}
	return 0;
}
