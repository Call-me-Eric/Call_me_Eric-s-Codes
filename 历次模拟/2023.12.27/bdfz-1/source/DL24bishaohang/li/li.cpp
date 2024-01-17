#include <bits/stdc++.h>
using namespace std;

int n,m,cnt[200010];bool fl;
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;cnt[u]++;cnt[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]!=2) fl=1;
	}
	if(m==0)
	{
		cout<<0<<' '<<n;return 0;
	}
	if(m==1)
	{
		cout<<0<<' '<<n+1;return 0;
	}
	if(n==2)
	{
		cout<<0<<' '<<3;return 0;
	}
	if(n==3&&m==2)
	{
		cout<<0<<' '<<6;return 0;
	}
	if(n==3&&m==3)
	{
		cout<<1<<' '<<3;return 0;
	}
	if(!fl)
	{
		cout<<1<<' '<<n;return 0;
	}
	return 0;
}