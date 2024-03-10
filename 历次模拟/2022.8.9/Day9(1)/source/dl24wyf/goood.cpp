#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,U[N],V[N];
int head[N][3],cnt[3];
struct node{
	int nxt,to;
}e[N][3];
void add(int u,int v,int op){
	e[++cnt[op]][op].to=v;e[cnt[op]][op].nxt=head[u][op];head[u][op]=cnt[op];
}
bool vis[N][3];	
void dfs(int u,int op)
{
	vis[u][op]=1;
	for(int i=head[u][op];i;i=e[i][op].nxt)
	{
		int v=e[i][op].to;
		if(!vis[v][op]) dfs(v,op);
	}
}
int ans[N],tot;
int main()
{
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&U[i],&V[i]);add(U[i],V[i],1),add(V[i],U[i],2);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) vis[j][1]=vis[j][2]=0;
		dfs(i,1);dfs(i,2);
		bool flag=0;
		for(int j=1;j<=n;j++) 
		{
			if(!vis[j][1]&&!vis[j][2]) {flag=1;break;}
		}
		if(!flag) ans[++tot]=i;
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++) cout<<ans[i]<<" ";
	return 0;
}
/*
3 3
1 2
2 3
3 2
*/
