#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int inf=999999999;
int id,p[N];
int f[N][5],a[N];
int n;
struct Node
{
	int to,nxt;
}e[N*2];
void add(int x,int y)
{
	id++;
	e[id].to=y;
	e[id].nxt=p[x];
	p[x]=id;
}
void dfs(int u,int fa)
{
	int flag=0;
	int t0=0,t1=0,t2=0,tt1=0;
	for(int i=p[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		t0+=f[v][1];
		tt1+=min(f[v][2],f[v][1]);
		if(f[v][2]<=f[v][1])
		{
			flag=1;
		}
		if(t1==0||f[v][2]-f[v][1]<f[t1][2]-f[t1][1])
		{
			t1=v;
		}
		t2+=min(min(f[v][0],f[v][1]),f[v][2]);
	}
	f[u][0]=t0;
	if(flag)
	{
		f[u][1]=tt1;
	}
	else
		f[u][1]=t1?t0-f[t1][1]+f[t1][2]:inf;
	f[u][2]=t2+a[u];
}
signed main()
{
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	cout<<min(f[1][1],f[1][2]);
}
/*
7
13 20 1 20 6 9 8
1 2
1 3
2 4
2 5
3 6
5 7
*/
