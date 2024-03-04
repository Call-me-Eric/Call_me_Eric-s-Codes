#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#define ll long long
#define ull unsigned long long
#define lowbit(x) x & (-x)
#define re register
#define rep(i,a,b) for(re int i(a);i <= b;i ++)
#define rrep(i,a,b) for(re int i(a);i >= b;i --)
#define mp make_pair
#define fir first
#define sec second

using namespace std;
inline int read(){
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const int M = 60;
const int N = M * M * 2;
const int MM = 1e5 + 1;
int X[M][M],Y[M][M],vis[M][M];
pair<int,int> las[M][M];
pair<int,int> mst[M][M];
char MAP[M][M];
stack<int> s;
struct node{
	int to;
	int pre;
}e[MM];
int head[N];
int cnt = 0;
int dfn[N];
int low[N];
int dfc;
int scccnt;
int scc[N];
int no_ans;
int rcd[N];
int cant[N];

inline int add_edge(int u,int v){
	e[++ cnt].to = v;
	e[cnt].pre = head[u];
	head[u] = cnt;
}
int tarjan(int x){
	s.push(x);
	dfn[x] = low[x] = ++dfc;
	scc[x] = 1;
	for(re int i(head[x]);i;i = e[i].pre){
		int y = e[i].to;
		if(!scc[y]){
			tarjan(y);
			low[x] = min(low[x],low[y]);
		}
		else if(scc[y] == 1) low[x] = min(low[x],dfn[y]);
	}
		if(low[x] == dfn[x]){
			rcd[x] = ++ scccnt;
			scc[x] = 2;
			for(re int j = s.top();j != x;s.pop(),j = s.top()){
				rcd[j] = scccnt;
				scc[j] = 2;	
			}
			s.pop();
		}
	return 0;
}
#define SRC(p,q,_dx,_dy){\
for(int dx = _dx,dy = _dy,i = x + dx,j = y + dy;((i) >= 1 && (i) <= (n) && (j) >= 1 && (j) <= (m) && MAP[i][j] != '#');i += dx,j += dy) \
if(MAP[i][j] == '/' || MAP[i][j] == '\\') find(dx,dy,MAP[i][j]);\
else if(MAP[i][j] == '.'){\
if(!vis[i][j]) mst[i][j] = mp(q,p);\
else if(mst[i][j] != mp(q,p)) mst[i][j] = mp(0,0);\
if(!vis[i][j]) las[i][j] = mp(q,p);\
else if(las[i][j] != mp(q,p) && las[i][j] != mp(p,q)) add_edge(p,las[i][j].fir),add_edge(las[i][j].sec,q);\
vis[i][j] = 1;\
}\
}
#define GFIND(p,_dx,_dy)\
for(re int dx = _dx,dy = _dy,i = x + dx,j = y + dy;((i) >= 1 && (i) <= (n) && (j) >= 1 && (j) <= (m) && MAP[i][j] != '#');i += dx,j += dy){\
if(MAP[i][j] == '|' || MAP[i][j] == '-'){\
cant[p] = 1;break;\
}\
else if(MAP[i][j]== '/' || MAP[i][j] == '\\') find(dx,dy,MAP[i][j]);\
}
inline int find(int &dx,int &dy,char c){
	if(c == '\\') swap(dx,dy);
	else{
		if(dx) dy = -dx,dx = 0;
		else dx = -dy,dy = 0;
	}
	return 0;
}
inline int getcant(int x,int y,int n,int m){
	int p = X[x][y],q = Y[x][y];
	GFIND(p,0,1) GFIND(p,0,-1)
	GFIND(q,1,0) GFIND(q,-1,0)
	if(cant[p] && cant[q]) return no_ans = 1;
	return 0;
}
inline int go(int x,int y,int n,int m){
	int p = X[x][y],q = Y[x][y];
	cant[p] = cant[q] = 0;
	getcant(x,y,n,m);if(no_ans) return 0;
	if(!cant[q]){
		SRC(p,q,1,0)
		SRC(p,q,-1,0)
	}
	if(!cant[p]){
		SRC(q,p,0,1)
		SRC(q,p,0,-1)
	}
	return 0;
}
signed main(){
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	int T = read();
	while(T --){
		int n = read();
		int m = read();
		int c = 0;
		no_ans = 0;
		cnt = 0;
		rep(i,1,n) scanf("%s",MAP[i] + 1);
		rep(i,1,n){
			rep(j,1,m){
				las[i][j] = mp(0,0);
				vis[i][j] = 0;
			}
		} 
		rep(i,1,n){
			rep(j,1,m){
				if(MAP[i][j] == '|' || MAP[i][j] == '-'){
					X[i][j] = ++ c;
					Y[i][j] = ++ c;
					head[c - 1] = head[c] = 0;
					go(i,j,n,m);
				}
				else X[i][j] = 0;
				if(no_ans){
					printf("IMPOSSIBLE\n");
					goto END_LOOP;
				}
			}
		}
		rep(i,1,n){
			rep(j,1,m){
				if(X[i][j]){
					int p = X[i][j],q = Y[i][j];
					if(cant[p]) add_edge(p,q);
					if(cant[q]) add_edge(q,p);
				}
			}
		}
		rep(i,1,n){
			rep(j,1,m){
				if(MAP[i][j] == '.' && !vis[i][j]){
					printf("IMPOSSIBLE\n");
					goto END_LOOP;
				}
			}
		}
		rep(i,1,n){
			rep(j,1,m){
				if(MAP[i][j] == '.' && mst[i][j].sec) add_edge(mst[i][j].sec,mst[i][j].fir);
			}
		}
		memset(scc,0,sizeof(int) * (c + 1)),dfc = 0,scccnt = 0;
		rep(i,1,c) if(!scc[i]) tarjan(i);
	    rep(i,1,n){
	    	rep(j,1,m){
	    		if(X[i][j]){
	    			int p = X[i][j],q = Y[i][j];
	    			int x = rcd[p],y = rcd[q];
	    			if(x == y){
	    				printf("IMPOSSIBLE\n");
					    goto END_LOOP;
					}
					else if(x < y) MAP[i][j] = '-';
					else MAP[i][j] = '|';
				}
			}
		}
		printf("POSSIBLE\n");
		rep(i,1,n){
			rep(j,1,m){
				printf("%c",MAP[i][j]);
			}
			cout << endl;
		}
		END_LOOP : continue;
	}
	return 0;
}

