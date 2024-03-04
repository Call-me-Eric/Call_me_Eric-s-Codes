#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3 ) + (ch ^ 48);ch = getchar();}
	return x * f;
}
inline void write(int x){if(!x)return;write(x / 10);putchar('0' + (x % 10));}
const int maxn = 1e6 + 10;
int n;
int f[maxn][4];
//f[i][1] = return to i;
//f[i][0] = cannot leave i max;f[i][2] = cannot leave i second max;
//f[i][3] = max point(cannot leave)
int head[maxn], tot;
struct edge{
	int to, nexte, wei;
	edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

void dfs(int u,int fa){
	int mx = 0, maxx = 0, point = 0;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == fa)continue;
		dfs(v, u);
		if(e[i].wei == 1){mx = max(mx,f[v][0] + 1);continue;}
		int tmp = f[v][1] +  e[i].wei - (e[i].wei % 2);
		f[u][1] += tmp;
		int tmp2 = f[v][0] + e[i].wei - (e[i].wei % 2 == 0) - tmp;
		if(mx < tmp2){point = v;maxx = mx;mx = tmp2;}
		else if(maxx < tmp2)maxx = tmp2;
	}
	f[u][0] = mx + f[u][1];f[u][2] = maxx += f[u][1];f[u][3] = point;
}
int ans = 0;
void dfs1(int u,int fa){
	
}
bool book[maxn];
signed main(){
//	freopen("plan.in","r",stdin);
//	freopen("plan.out","w",stdout);
int T = read();
while(T--){
	tot = 0;
	n = read();int u, v, w;
	for(int i = 1;i <= n;i++){head[i] = 0;}
	for(int i = 1;i < n;i++){
		u  =read(); v = read(); w = read();
		add(u , v, w);add(v, u, w);
	}
	dfs(1, 0);ans = max(ans,max(f[1][0],f[1][1]));
	dfs1(1, 0);
	printf("%lld\n",ans);
}
	return 0;
}