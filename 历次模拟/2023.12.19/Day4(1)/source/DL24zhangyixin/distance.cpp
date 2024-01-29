#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1000100;
const int mod=1e9+7;
int n,m,k,x[N],y[N],mx;
struct node{
	int to,nxt,w;
}e[N<<2];
int head[N],cnt,num;
void add(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int dis[N],pre[N],path[N],val=1;
bool vis[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
void dij()
{
	memset(vis,0,sizeof(vis));
	memset(pre,-1,sizeof(pre));
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[1]=0;pre[1]=-1;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to,z=e[i].w;
			if(dis[y]>dis[x]+z)
			{
				dis[y]=dis[x]+z;
				pre[y]=x;
				q.push(make_pair(dis[y],y));
			}
		}
	}
}
signed main()
{
	freopen("distance.in","r",stdin);
	freopen("distance.out","w",stdout);
	scanf("%lld %lld %lld",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%lld %lld",&x[i],&y[i]);
	}
//	mx=max(abs(x[1]-x[k]),abs(y[1]-y[k]));
	for(int i=1;i<=k;i++)
	{
		for(int j=i+1;j<=k;j++)
		{
			//if(mx<=max(abs(x[i]-x[j]),abs(y[i]-y[j]))) continue;
			val=1;
			for(int s=1;s<=max(abs(x[i]-x[j]),abs(y[i]-y[j]));s++) val*=2,val%=mod;
			add(i,j,val);
		//	printf("i=%d j=%d w=%d\n",i,j,val);
			add(j,i,val);
		}
	}
	dij();
	int now=k;
	num=0;
	path[++num]=1;
	while(pre[now]!=-1)
	{
        path[++num]=pre[now];
        now=path[now];
    }
    path[++num]=k;
	printf("%lld\n",num);
	for(int i=1;i<=num;i++)
	printf("%lld ",path[i]);
	return 0;
} 
