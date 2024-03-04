#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e6+5, M=2e6+5;

int n, m;
struct Edge{int to, nt, w;} e[M<<1]; int hd[N], ect=1;
void ade(int u, int v, int w){e[++ect]={v, hd[u], w}; hd[u]=ect;}

int dfc, dfn[N], low[N], pre[N], touch[N];
vector<int> blo[N]; int bid;
int stk[N], tp;

void tarjan(int u){
	dfn[u]=low[u]=++dfc;
	stk[++tp]=u;
	for(int i=hd[u]; i; i=e[i].nt){
		int v=e[i].to, w=e[i].w;
		if(!dfn[v]){
			pre[v]=i;
			tarjan(v);
			low[u]=min(low[u], low[v]);
			
			if(low[v]>=dfn[u]){
				++bid;
				if(touch[stk[tp]]) blo[bid].push_back(e[touch[stk[tp]]].w);
				while(stk[tp]!=u) blo[bid].push_back(e[pre[stk[tp--]]].w);
			}
		}
		else if(dfn[v]<=low[u]){
			if(i!=(pre[u]^1)) touch[u]=i;
			low[u]=dfn[v];
		}
	}
}

signed main(){
	freopen("inazuma.in", "r", stdin);
	freopen("inazuma.out", "w", stdout);
	n=rd(), m=rd();
	for(int i=1, u, v, w; i<=m; i++){
		u=rd(), v=rd(), w=rd();
		ade(u, v, w), ade(v, u, w);
	}
	
	tarjan(1);
	
	int ans=INT_MAX;
	for(int i=1; i<=bid; i++){
		if(blo[i].size()==1) ans=min(ans, blo[i][0]);
		else{
			int mn1=INT_MAX, mn2=INT_MAX;
			for(int v:blo[i]){
				if(v<mn1) mn2=mn1, mn1=v;
				else if(v<mn2) mn2=v;
			}
			ans=min(ans, mn1+mn2);
		}
	}
	printf("%d\n", ans);
	return 0;
}
