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

const int N=505, M=1e5+5;
int n, m;

struct Edge{int to, nt, w, c;} e[M]; int hd[N], ect=1;
void _ade(int u, int v, int w, int c){e[++ect]={v, hd[u], w, c}; hd[u]=ect;}
void ade(int u, int v, int w, int c){_ade(u, v, w, c), _ade(v, u, 0, -c);}

int S, T, pre[N];
int dis[N]; bool vis[N];
int fn, cn;
bool spfa(){
	memset(dis, 63, sizeof(dis)); dis[S]=0;
	queue<int> q;
	while(!q.empty()){
		int u=q.front(); vis[u]=0; q.pop();
		for(int i=hd[u]; i; i=e[i].nt) if(e[i].w){
			int v=e[i].to, c=e[i].c;
			if(dis[v]>dis[u]+c){
				pre[v]=i;
				dis[v]=dis[u]+c;
				if(!vis[v]) q.push(v), vis[v]=1;
			}
		} 
	}
	if(dis[T]==dis[T+1]) return 0;
	fn++;
	for(int i=pre[T]; i; i=pre[e[i^1].to]) cn+=e[i].c, e[i].w--, e[i^1].w++;
}

int id(int x, int y, int type){
	return type*n*n+n*(x-1)+y;
}

pii s[N], t[N];
const int dx[]={0, 0, 1, -1}, dy[]={1, -1, 0, 0};

signed main(){
	n=rd(), m=rd();
	S=0, T=2*n*n+1;
	for(int i=1; i<=m; i++){
		s[i]={rd(), rd()};
		t[i]={rd(), rd()};
		ade(S, id(s[i].fr, s[i].sc, 0), 1, 0);
		ade(id(t[i].fr, t[i].sc, 1), T, 1, 0);
	}
	for(int x=1; x<=n; x++){
		for(int y=1; y<=m; y++){
			ade(id(x, y, 0), id(x, y, 1), 1, 1);
			for(int i=0; i<4; i++){
				int nx=x+dx[i], ny=y+dy[i];
				if(nx>0 && nx<=n && ny>0 && ny<=n){
					ade(id(x, y, 1), id(nx, ny, 0), 1, 0);
				}
			}
		}
	}
	while(spfa());
	printf("%d\n", cn);
//	for(int x=1; x<=n; x++){
//		for(int y=1; y<=m; y++){
////			ade(id(x, y, 0), id(x, y, 1), 1);
////			for(int i=0; i<4; i++){
////				int nx=x+dx[i], ny=y+dy[i];
////				if(nx>0 && nx<=n && ny>0 && ny<=n){
////					ade(id(x, y, 1), id(nx, ny, 0), 1);
////				}
////			}
//			dfs(1, 0);
//		}
//	}
	return 0;
}
/**/
