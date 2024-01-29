#include <bits/stdc++.h>
using namespace std;

int t,n,m,a[100010],c[100010],dis[1010],fa[1010],cnt;
int head[1010];
bool vis[1010];
struct edge
{
	int next,to,va;
}e[4010];
void ad3(int x,int v)
{
	for(int i=x;i<=n;i+=(i&-i)) c[i]+=v;
}
int sum3(int x)
{
	int res=0;
	for(int i=x;i;i-=(i&-i)) res+=c[i];
	return res;
}
void ad5(int u,int v,int va)
{
	e[++cnt].to=v;
	e[cnt].va=va;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dfs5(int x)
{
	for(int i=head[x];i!=-1;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa[x]) continue;
		fa[v]=x;dis[v]=dis[x]+e[i].va;
		dfs5(v);
	}
}
void dij7()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	int u=1;
	for(int ii=1;ii<n;ii++)
	{
		vis[u]=1;int minx=0x3f3f3f3f;
		for(int i=head[u];i!=-1;i=e[i].next)
		{
			int v=e[i].to;
			if(vis[v]) continue;
			dis[v]=min(dis[v],dis[u]+e[i].va);
		}
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			if(minx>dis[i])
			{
				minx=dis[i];u=i;
			}
		}
	}
}
void S8FA()
{
	queue<int> q;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push(1);vis[1]=1;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>(dis[u]^e[i].va))
			{
				dis[v]=dis[u]^e[i].va;
				if(!vis[v])
				{
					vis[v]=1;q.push(v);
				}
			}
		}
	}
}
int main()
{
	freopen("crack.in","r",stdin);
	freopen("crack.out","w",stdout);
	cin>>t;
	if(t==3)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];ad3(i,a[i]);
		}
		for(int i=1;i<=m;i++)
		{
			int l,r;cin>>l>>r;
			cout<<sum3(r)-sum3(l-1)<<'\n';
		}
	}
	if(t==4)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			for(int j=1;j<=i;j++)
			{
//				xsum[j][i]=xsum[j][i-1]^a[i];
			}
		}
		for(int i=1;i<=m;i++)
		{
			int l,r;cin>>l>>r;int ans=0;
//			for(int j)
		}
	}
	if(t==5)
	{
		cin>>n;memset(head,-1,sizeof(head));
		for(int i=1;i<n;i++)
		{
			int u,v,va;cin>>u>>v>>va;
			ad5(u,v,va);ad5(v,u,va);
		}
		dfs5(1);int manx=0,j=0;
		for(int i=1;i<=n;i++)
		{
			if(dis[i]<=manx) continue;
			j=i;manx=dis[i];
		}
		memset(dis,0,sizeof(dis));
		memset(fa,0,sizeof(fa));
		dfs5(j);
		manx=0;
		for(int i=1;i<=n;i++)
		{
			if(dis[i]>manx) manx=dis[i];
		}
		cout<<manx;
	}
	if(t==7)
	{
		cin>>n>>m;
		memset(head,-1,sizeof(head));
		for(int i=1;i<=m;i++)
		{
			int u,v,va;cin>>u>>v>>va;
			ad5(u,v,va);ad5(v,u,va);
		}
		dij7();
		cout<<dis[n];
	}
	if(t==8)
	{
		cin>>n>>m;
		memset(head,-1,sizeof(head));
		for(int i=1;i<=m;i++)
		{
			int u,v,va;cin>>u>>v>>va;
			ad5(u,v,va);ad5(v,u,va);
		}
		S8FA();
		cout<<dis[n];
	}
	return 0;
}