#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0 , f  = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int x, y;

int head[maxn], tot;
struct edge{
	int to, nexte;
	edge(int t = 0,int ne = 0):to(t),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int col[maxn];
int dp[maxn][3];
int mx[maxn][3];
int dep[maxn], fa[maxn];
void dfs(int u,int f,int color){
	col[u] |= color;dep[u] = dep[f] + 1;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f)continue;
		if(v == x || v == y)continue;fa[v] = u;
		dfs(v, u, color);dp[u][color] = max(dp[v][color] + 1,dp[u][color]);
	}
}
void dfs1(int u,int f,int color){
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f)continue;
		if(v == x || v == y)continue;
		if(col[v] != 3)continue;
		dfs1(v,u,color);mx[u][color] = max(mx[u][color],mx[v][color] + 1);
	}
}
bool flag1[maxn], flag2[maxn];
int maxx[maxn][3];
void dfs2(int u,int f,int color){
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f)continue;
		if(v == x || v == y)continue;
		if(col[v] != 3)continue;
		if(color == 1 && flag1[v])continue;
		if(color == 2 && flag2[v])continue;
		dfs2(v,u,color);maxx[u][color] = max(maxx[u][color],maxx[v][color] + 1);
	}
}
signed main(){
	freopen("oshinoko.in","r",stdin);
	freopen("oshinoko.out","w",stdout);
int T = read();
while(T--){
	n = read(); m = read(); int u, v;
	x = read(); y = read();
	for(int i = 1;i < n;i++){
		u = read(); v = read();
		add(u, v); add(v, u);
	}
	int ans = 0;
	dfs(x,0,1);dfs(y,0,2);
	int dist = dep[x] - dep[y];
	int tmp = x;
	for(int i = 1;i <= dist / 2;i++)tmp = fa[tmp];
	if(dist % 2)flag1[fa[tmp]] = flag2[tmp] = 1;
	else flag1[fa[tmp]] = flag2[fa[tmp]] = 1;
	dfs1(x,0,1);dfs1(y,0,2);
	dfs2(x,0,1);dfs2(y,0,2);
	int dist1 = dp[x][1], dist2 = dp[y][2];
	int dist3 = mx[x][1], dist4 = mx[y][2];
	int dist5 = maxx[x][1], dist6 = maxx[y][2];
	if(dist1 >= dist3 && dist1 >= dist5){
		ans = (dist1 > max(dist2,max(dist4,dist6)));
	}
	else if(dist3 >= dist1 && dist3 >= dist5){
		ans = (dist3 > (max(dist2,dist6)));
	}
	else{
		if(dist % 2){
			ans = (max(dist1,dist5) > max(dist2,max(dist4,dist6)));
		}
		else ans = (dist3 > max(dist2,dist6));
	}
	printf("%d\n",ans);
}
	return 0;
}
