#include <bits/stdc++.h>
using namespace std;

int n,m,k,dis[510],lst[510],head[510],cnt,pat[510];
bool vis[510];
struct edge
{
	int next,to,va;
}e[250010];
struct dian
{
	int x,y;
}a[510];
void ad(int u,int v,int va)
{
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].va=va;
	head[u]=cnt;
}
int qqpow(int x,int b)
{
	if(b==1) return x;
	if(b%2==0) return qqpow(x*x,b/2);
	return qqpow(x*x,b/2)*x;
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
			if(dis[v]>dis[u]+e[i].va)
			{
				dis[v]=dis[u]+e[i].va;
				lst[v]=u;
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
	freopen()
	cin>>n>>m>>k;
	memset(head,-1,sizeof(head));
	if(n<=500&&m<=500&&k<=500)
	{
		for(int i=1;i<=k;i++) cin>>a[i].x>>a[i].y;
		memset(e,0x3f,sizeof(e));
		for(int i=1;i<=k;i++)
		{
			for(int j=1;j<=k;j++)
			{
				if(i==j) continue;
				int len=qqpow(2,max(abs(a[i].x-a[j].x),abs(a[i].y-a[j].y)));
				ad(i,j,len);ad(j,i,len);
			}
		}
		S8FA();
		cout<<dis[k]<<'\n';
		int now=k;
		for(int i=k;i;i--)
		{
			pat[i]=now;
			now=lst[now];
		}
		for(int i=1;i<=k;i++)
		{
			if(pat[i]) cout<<pat[i]<<' ';
		}
	}
	return 0;
}