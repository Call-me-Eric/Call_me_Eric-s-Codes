#include<bits/stdc++.h>
using namespace std;
const int N=1010*1010;
int n,m,a[N],d[N],t[N],mp[N],low[N],dfn[N],l,scc[N],c;
bool vis[N];
char ch;
int id(int x,int y){return (x-1)*m+y;}
vector<int> h[N];
stack<int> s;
void tarjan(int u){
	s.push(u);
	dfn[u]=low[u]=++l;
//	for(int i=0;i<g[u].size();i++){
		int v=mp[u];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(!scc[v])low[u]=min(low[u],dfn[v]);
//	}
	if(dfn[u]==low[u]){
		c++;int v;
		do{
			v=s.top(),s.pop();
			scc[v]=c,t[c]+=a[v];
//			printf("%d ",v);
		}while(u!=v);//puts("");
	}
}
void work(){
	for(int i=1;i<=n*m;i++)
		if(!dfn[i])tarjan(i);
}
int dfs(int u){
	if(vis[scc[u]])return t[scc[u]];
	vis[scc[u]]=1;
	if(scc[mp[u]]==scc[u])return t[scc[u]];
	return t[scc[u]]+=dfs(mp[u]);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
//			scanf("%c",&ch);
			if(ch=='L')mp[id(i,j)]=id(i,j-1);
			if(ch=='U')mp[id(i,j)]=id(i-1,j);
			if(ch=='R')mp[id(i,j)]=id(i,j+1);
			if(ch=='D')mp[id(i,j)]=id(i+1,j);
		}
	}
	work();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",dfs(id(i,j)));
		}puts("");
	}
    return 0;
}
