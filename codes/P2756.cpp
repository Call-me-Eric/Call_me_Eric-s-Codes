#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e2 + 10,maxm = maxn * maxn, INF = 0x3f3f3f3f;
int n, m;

int head[maxn], tot = 1;
struct edge{
	int to, nexte, cap, flow;
	edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}

int dep[maxn], cur[maxn];
int dfs(int u,int flow,int T){
	// printf("%lld\n",u);
	if(u == T)return flow;
	int rest = 0, tmp = 0;
	for(int i = cur[u];i && flow;i = e[i].nexte){
		cur[u] = i; int v = e[i].to;
		if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
			tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
			if(tmp == 0)dep[v] = INF;
			e[i].flow += tmp; e[i ^ 1].flow -= tmp;
			flow -= tmp;rest += tmp;
			if(!flow)return rest;
		}
	}
	return rest;
}
bool bfs(int S,int T){
	queue<int> que;
	for(int i = 1;i <= n + 3;i++){dep[i] = INF;cur[i] = 0;}
	que.push(S);dep[S] = 1; cur[S] = head[S];
	while(!que.empty()){
		int u = que.front(); que.pop();
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
			if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
				que.push(v);
				cur[v] = head[v];
				dep[v] = dep[u] + 1;
				if(v == T)return 1;
			}
		}
	}
	return 0;
}
int Dinic(int S,int T){
	int mxflow = 0;
	while(bfs(S,T)){mxflow += dfs(S,INF,T);}
	return mxflow;
}

signed main(){
	n = read(); m = read();int u, v;
	int S = n + 1, T = n + 2;
	for(int i = 1;i <= m;i++)addd(S,i,1);
	for(int i = m + 1;i <= n;i++)addd(i,T,1);
	while(scanf("%d%d",&u,&v),(u != -1 && v != -1)){addd(u, v, 1);}
	int ans = Dinic(S,T);
	printf("%d\n",ans);
	for(u = 1;u <= m;u++){
		v = 0;
		for(int i = head[u];i;i = e[i].nexte){
			if(e[i].cap == e[i].flow && e[i].cap == 1){
				v = e[i].to;break;
			}
		}
		if(v)printf("%d %d\n",u,v);
	}
	return 0;
}
