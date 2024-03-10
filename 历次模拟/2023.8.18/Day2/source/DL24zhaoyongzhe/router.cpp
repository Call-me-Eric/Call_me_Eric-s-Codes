#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int n;
int a[maxn];

int head[maxn], tot;
struct edge{
	int to, nexte;
	edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int f[maxn][2][2];
void dfs(int u,int fa){
	f[u][1][1] = a[u];
	int minval = 0x3f3f3f3f3f3f, book = 0, book1 = 0;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == fa)continue;
		book1 = 1; dfs(v,u);
		f[u][0][1] += min(f[v][0][1],f[v][1][1]);
		f[u][0][0] += f[v][0][1];
		f[u][1][1] += min(f[v][0][0], min(f[v][0][1],f[v][1][1]));
		if(f[v][1][1] <= f[v][0][1])book = 1;
		if(f[v][0][1] == 0x3f3f3f3f3f3f)continue;
		minval = (minval >= (f[v][1][1] - f[v][0][1]) ? ((f[v][1][1] - f[v][0][1])) : (minval));
	}
	if(!book){f[u][0][1] += minval;}
	if(!book1){f[u][0][1] = 0x3f3f3f3f3f3f;}
}

signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n = read(); int u, v;
	for(int i = 1;i <= n;i++)a[i] = read();
	for(int i = 1;i < n;i++){
		u = read(); v = read();
		add(u, v);add(v, u);
	}
	dfs(1,0);
	printf("%lld\n", min(f[1][0][1],f[1][1][1]));
	return 0;
}

