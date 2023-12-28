#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=5005,maxm=1e5+5;
int head[maxn],cnt,dis[maxn],a[10][505],b[10][505],n,k;
struct edge{int to,nxt,w;}e[maxm*2];
struct node
{
	int id,d;
	bool friend operator < (node a,node b){return a.d>b.d;}
};
priority_queue<node> q;
bool vis[maxn];

void add(int x,int y,int z){e[++cnt]=(edge){y,head[x],z},head[x]=cnt;}

void dij(int s)
{
	memset(dis,0x3f3f3f,sizeof dis);
	memset(vis,0,sizeof vis);
	q.push((node){s,0}),dis[s]=0;
	while(!q.empty())
	{
		int x=q.top().id;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].nxt)
			if(dis[e[i].to]>dis[x]+e[i].w) dis[e[i].to]=dis[x]+e[i].w,q.push((node){e[i].to,dis[e[i].to]});
	}
}

void sub1()
{
	for(int i=1;i<=n;i++) cin>>a[1][i];
	for(int i=1;i<=n;i++) cin>>b[1][i];
	int m;cin>>m;
	for(int i=1,u,v,w;i<=m;i++) cin>>u>>v>>w,add(u,v,w),add(v,u,w);
	dij(1);
	cout<<dis[n]+a[1][1]+b[1][n];
}

signed main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	cin>>n>>k;
	if(k==1) sub1(),exit(0);
	for(int t=1;t<=k;t++)
	{
		for(int i=1;i<=n;i++) cin>>a[t][i];
		for(int i=1;i<=n;i++) cin>>b[t][i];
		int m;cin>>m;
		for(int i=1;i<=m;i++)
		{
			int u,v,w;cin>>u>>v>>w;
			add(u+(i-1)*n,v+(i-1)*n,w),add(v+(i-1)*n,u+(i-1)*n,w);
		}
	}
	for(int i=1;i<=k;i++) add(0,(i-1)*n+1,a[i][1]);
	for(int i=2;i<n;i++)
		for(int t=1;t<=k;t++)
			for(int j=1;j<=k&&j!=t;j++)
				add((t-1)*n+i,(j-1)*n+i,b[t][i]+a[j][i]),add((j-1)*n+i,(t-1)*n+i,b[j][i]+a[t][i]);
//	int ans=LLONG_MAX;
//	for(int i=1;i<=k;i++)
//	{
//		dij((i-1)*n+1);
//		for(int j=1;j<=k;j++)
//			ans=min(ans,dis[j*n]+b[j][n]+a[i][1]);
//	}
//	cout<<ans<<endl;
	dij(0);
	int ans=LLONG_MAX;
	for(int i=1;i<=k;i++)
		ans=min(ans,dis[i*n]+b[i][n]);
	cout<<ans;
//	cout<<dis[n]<<' '<<dis[n*2];
	return 0;
}
