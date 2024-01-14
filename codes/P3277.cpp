#include<bits/stdc++.h>
//#define int long long
using namespace std;

inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 40 * 40 * 40 + 100,maxm = 2e6 + 10, INF = 0x3f3f3f3f;
int D, x, y, z;

int head[maxn], tot = 1;
struct edge{
	int to, nexte, cap, flow;
	edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}
int total, id[41][41][41];
int val[41][41][41];
inline int getid(int x,int y,int z){
	if(id[x][y][z])return id[x][y][z];
	return id[x][y][z] = ++total;
}

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
	for(int i = 1;i <= total;i++){dep[i] = INF;cur[i] = 0;}
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
const int dx[4] = { 0,-1, 1, 0};
const int dy[4] = {-1, 0, 0, 1};

signed main(){
	x = read(); y = read(); z = read();
	D = read();int S = ++total;int T = ++total;
	for(int k = 1;k <= z;k++){
		for(int i = 1;i <= x;i++){
			for(int j = 1;j <= y;j++){
				val[i][j][k] = read();
				if(k != z){addd(getid(i,j,k),getid(i,j,k + 1),val[i][j][k]);}
				else addd(getid(i,j,k),T,val[i][j][k]);
				if(k == 1){addd(S,getid(i,j,k),INF);}
				if(k > D)
				for(int l = 0;l < 4;l++){
					int nx = i + dx[l], ny = j + dy[l];
					if(nx < 1 || nx > x || ny < 1 || ny > y)continue;
					addd(getid(i,j,k),getid(nx,ny,k - D),INF);
				}
			}
		}
	}
	printf("%d\n",Dinic(S,T));
	return 0;
}
