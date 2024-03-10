#include<bits/stdc++.h>
using namespace std;
int n,m,head[1000010],tot;
int u[1000010],v[1000010];
struct edge
{
	int to,next;
} e[5000010];
void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].next=head[u];
	head[u]=tot;
}
int cnt,num,ans[1000010];
bool vis[1000010];/*
void tarjan(int u)
{
	dfn[u]=low[u]=++dfs_clock;
	vis[u]=1,st[++top]=u;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int s;
		scc++;
		do
		{
			s=st[top--];
			vis[s]=0;
			col[s]=scc;
		}while(s!=u)
	}
}*/
int cd[1000010];
bool check()
{
	for(int i=1; i<=n; i++) if(!vis[i]) return 0;
	return 1;
}//是否所有点均被染色
int flag,k,opt;
void dfs(int u)
{
	num++;
	vis[u]=1;
	if(num==n||cd[u]==0)
	{
		if(check()) flag=1;
		else flag=0;//环
	}
	for(int i=head[u]; i; i=e[i].next)
	{
		int v=e[i].to;
		if(!vis[v])
		{
			//cout<<u<<"->"<<v<<endl;
			dfs(v);
		}
	}
}
void build(int op)
{
	if(op==0) for(int i=1; i<=m; i++) add_edge(u[i],v[i]);
	if(op==1) for(int i=1; i<=m; i++) add_edge(v[i],u[i]);
}
int main()
{
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		cd[u[i]]++;
	}
	build(0);opt=0;
	for(int i=1; i<=n; i++)
	{
		//cout<<i<<":";
		flag=0;
		k=i;
		dfs(i);
		if(flag)
		{
			//cout<<"!!!";
			num=0,ans[++cnt]=i;
			memset(vis,0,sizeof vis);
		}
	}
	tot=0;
	num=0;
	memset(e,0,sizeof e);
	memset(vis,0,sizeof vis);
	memset(head,0,sizeof head);

	build(1);opt=1;
	for(int i=1; i<=n; i++)
	{
		//cout<<i<<":";
		flag=0;
		k=i;
		dfs(i);
		if(flag)
		{
			//cout<<"!!!";
			num=0,ans[++cnt]=i;
			memset(vis,0,sizeof vis);
		}
	}
	sort(ans+1,ans+cnt+1);
	printf("%d\n",cnt);
	for(int i=1; i<=cnt; i++) printf("%d ",ans[i]);
	return 0;
}
/*
6 7
1 2
1 3
2 4
3 4
4 5
5 6
6 5
*/
