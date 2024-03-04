#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int inf=1e9;
vector<int> a[N];
int n,ans;
struct Node
{
	int x,y;
	bool operator<(Node b)const
	{
		return x<b.x;
	}
};
bool check(int mid)
{
	priority_queue<pair<int,Node>> q;
	while(!q.empty())q.pop();
	int maxx=-inf;
	for(int i=1;i<=n;i++)
	{
		q.push({-a[i][0],{i,0}});
		maxx=max(maxx,a[i][0]);
	}
	while(1)
	{
		Node t=q.top().second;
		q.pop();
		if(maxx-a[t.x][t.y]<=mid)return true;
		if(t.y+1>=a[t.x].size())return false;
		q.push({-a[t.x][t.y+1],{t.x,t.y+1}});
		maxx=max(maxx,a[t.x][t.y+1]);
	}
}
signed main()
{
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%lld",&x);
		for(int j=1;j<=x;j++)
		{
			scanf("%lld",&y);
			a[i].push_back(y);
		}
//		if(!minn||a[minn].size()>a[i].size())minn=i;
		sort(a[i].begin(),a[i].end());
	}
	int l=0,r=2*inf;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	cout<<ans;
	return 0;
}
