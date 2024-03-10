#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
map<pair<int,int>,int> mp;
bool vis[N];
int tot;
int id,p[N],in[N];
int n,m;
int siz[N];
struct Node
{
	int to,nxt;
}e[N*2];
void add(int x,int y)
{
	in[y]++;
	id++;
	e[id].to=y;
	e[id].nxt=p[x];
	p[x]=id;
}
int getid(int x,int y)
{
	pair<int,int> p={x,y};
	if(mp.count(p))return mp[p];
	return mp[p]=++tot;
}
void work(int x,int y)
{
	if(vis[getid(x,y)])return;
	vis[getid(x,y)]=1;
	int tx,ty;
	if(x>y)
	{
		tx=x-y;
		ty=y;
	}
	else
	{
		tx=x;
		ty=y-x;
	}
	if(tx==0||ty==0)return;
	add(getid(tx,ty),getid(x,y));
	work(tx,ty);
}
void dfs(int u,int fa)
{
	for(int i=p[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
signed main()
{
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		siz[getid(x,y)]++;
		work(x,y);
	}
	for(int i=1;i<=tot;i++)
	{
		if(!in[i])
		{
			add(0,i);
		}
	}
	dfs(0,0);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		if(!mp.count({x,y}))
		{
			cout<<0<<endl;
		}
		else
		{
			cout<<siz[getid(x,y)]<<endl;
		}
	}
}
