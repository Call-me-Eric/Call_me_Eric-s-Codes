#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
	long long xr=0,F=1; char cr;
	while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
	while(cr>='0'&&cr<='9') 
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
#define int long long
const int N=505;
int n,k,f[N][N];
struct subway
{
	int in[N],out[N],dis[N][N];
	struct edge{int nxt,to,w;} e[N<<2];
	int head[N],cnt=0;
	il void add(int u,int v,int w) {e[++cnt]={head[u],v,w};head[u]=cnt;}
	#define pii pair<int,int>
	#define fi first
	#define se second
	priority_queue<pii,vector<pii>,greater<pii> >q;
	void dij(int s)
	{
		memset(dis[s],0x3f,sizeof(dis[s]));
		dis[s][s]=0; q.push(pii(0,s));
		while(!q.empty())
		{
			int u=q.top().se,f=q.top().fi; q.pop();
			if(dis[s][u]!=f) continue;
			for(int i=head[u];i;i=e[i].nxt)
			{
				int v=e[i].to;
				if(dis[s][v]>dis[s][u]+e[i].w)
				{
					dis[s][v]=dis[s][u]+e[i].w;
					q.push(pii(dis[s][v],v));
				}
			}
		}
	}
	void init() {for(int i=1;i<=n;i++) dij(i);}
}a[10];
struct node
{
	int dis,u,s;
	friend bool operator <(const node &x,const node &y)
	{
		if(x.dis!=y.dis) return x.dis>y.dis;
		if(x.u!=y.u) return x.u>y.u;
		return x.s>y.s;
	}
};
priority_queue<node> q;
int ans=1e18;
void solve()
{
	memset(f,0x3f,sizeof(f));
	f[1][0]=0; q.push(node{0,1,0});
	while(!q.empty())
	{
		int u=q.top().u,s=q.top().s,dis=q.top().dis; q.pop();
		if(f[u][s]!=dis) continue;
		if(u==n) ans=min(ans,f[u][s]);
		for(int i=0;i<k;i++)
		{
			if(s>>i&1) continue;
			for(int v=1;v<=n;v++)
			{
				int w=a[i].dis[u][v]+a[i].in[u]+a[i].out[v];
				int t=s|(1<<i);
				if(f[v][t]>f[u][s]+w) f[v][t]=f[u][s]+w,q.push({f[v][t],v,t});
			}
		}
	}
}
signed main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	n=read(),k=read();
	for(int i=0;i<k;i++)
	{
		for(int j=1;j<=n;j++) a[i].in[j]=read();
		for(int j=1;j<=n;j++) a[i].out[j]=read();
		int m=read();
		for(int j=1;j<=m;j++) 
		{
			int u=read(),v=read(),w=read();
			a[i].add(u,v,w),a[i].add(v,u,w);
		}
		a[i].init();
	}
//	cerr<<"done init"<<endl;
	solve();
	printf("%lld\n",ans);
	return 0;
}
/*
4 2
1 2 1 4
4 3 2 1
4
2 1 2
2 3 39
4 2 48
3 4 1
1 1 2 2
1 0 0 1
3
1 4 29
2 3 3
4 3 7
*/
