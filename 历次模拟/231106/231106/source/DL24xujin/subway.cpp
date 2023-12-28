#include<bits/stdc++.h>
using namespace std;
#define int long long

inline int read()
{
	int x=0,f=1;
	char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x = (x*10)+(ch-'0');
		ch = getchar();
	}
	return x*f;
}

const int maxn = 507;
int n,k;
int a[10][maxn],b[10][maxn];
int m[10];
struct node
{
	int to,nxt,val;
}e[250009<<1];
int head[250009<<1],cnt;
inline void add(int u,int v,int w)
{
	e[++cnt].nxt = head[u];
	e[cnt].to = v;
	e[cnt].val = w;
	head[u] = cnt;
}
int dis[maxn];
bool vis[maxn];
inline void dij(int s)
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(vis,false,sizeof(vis));
	dis[s] = 0;
	priority_queue<pair<int,int> >q;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v = e[i].to;
			if(dis[v]<=dis[u]+e[i].val)
			{
				continue;
			}
			dis[v] = dis[u]+e[i].val;
		    q.push(make_pair(-dis[v],v));
		}
	}
}

signed main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	n = read(),k = read();
	for(int i=1;i<=k;++i)
	{
		for(int j=1;j<=n;++j) a[i][j] = read();
		for(int j=1;j<=n;++j) b[i][j] = read();
		m[i] = read();
		for(int j=1;j<=m[i];++j)
		{
		    int u = read(),v = read(),w = read();
		    add(u,v,w+a[i][u]+b[i][v]);
		    add(v,u,w+a[i][v]+b[i][u]);
		}
	}
	dij(1);
	cout<<dis[n];
	return 0;
}
