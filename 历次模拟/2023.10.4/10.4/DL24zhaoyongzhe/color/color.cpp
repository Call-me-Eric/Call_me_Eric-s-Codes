#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f =1 ;char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, m;

struct edg{
	int to, col, id;
	edg(int t = 0,int co = 0,int id = 0):to(t),col(co),id(id){}
	friend bool operator < (edg a,edg b){return a.col < b.col;}
};
vector<edg> e[maxn];
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
bool mergef(int x,int y){int fx = getf(x), fy = getf(y);if(fx == fy){return false;}fa[fx] = fy;return true;}
void init(){for(int i = 1;i <= n;i++)fa[i] = i;return;}
int getans(){int cnt = 0;for(int i = 1;i <= n;i++)cnt += (fa[i] == i);return cnt;}
int solve(int u,int v,int col){
	init();
	for(int i = 0;i < e[u].size();i++){if(e[u][i].to == v){e[u][i].col = col;break;}}
	for(int i = 0;i < e[v].size();i++){if(e[v][i].to == u){e[v][i].col = col;break;}}
	sort(e[u].begin(),e[u].end());sort(e[v].begin(),e[v].end());
	for(int i = 1;i <= n;i++){
		for(int j = 1;j < e[i].size();j++){
			if(e[i][j].col == e[i][j - 1].col){
				mergef(e[i][j].id,e[i][j - 1].id);
			}
		}
	}
	return getans();
}

signed main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n = read(); m = read();int u, v, col;
	for(int i = 1;i <= n;i++){
		u = read(); v = read(); col = read();
		e[u].push_back(edg(v,col,i));
		e[v].push_back(edg(u,col,i));
	}
	for(int i = 1;i <= n;i++)sort(e[i].begin(),e[i].end());
	for(int i = 1;i <= m;i++){
		u = read(); v = read(); col = read();
		printf("%d\n",solve(min(u,v),max(u, v),col));
	}
	return 0;
}
