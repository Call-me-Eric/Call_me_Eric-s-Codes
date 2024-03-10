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
int f[maxn][2];

int head[maxn], tot;
struct edge{
	int to, nexte, wei;
	edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

void dfs(int u,int fa){
	int mx = 0;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == fa)continue;
		dfs(v, u);
		if(e[i].wei == 1){mx = max(mx,f[v][0] + 1);continue;}
		int tmp = f[v][1] +  e[i].wei - (e[i].wei % 2);
		f[u][1] += tmp;
		mx = max(mx,f[v][0] + e[i].wei - (e[i].wei % 2 == 0) - tmp);
	}
	f[u][0] = mx + f[u][1];
}
bool book[maxn];
signed main(){
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
int T = read();
while(T--){
	tot = 0;
	n = read();int u, v, w;
	bool switchcase = (n > 3000);
//	switchcase = true;
	for(int i = 1;i <= n;i++){head[i] = 0;}
	for(int i = 1;i < n;i++){
		u  =read(); v = read(); w = read();
		add(u , v, w);add(v, u, w);
	}
if(!switchcase){
	int ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)f[j][0] = f[j][1] = 0;
		dfs(i,0);ans = max(ans,max(f[i][0],f[i][1]));
	}
	printf("%lld\n",ans);
}
else{
	//UDULRLRL
	srand(time(0));int ans = 0,u = 1;
	for(int i = min(n,(int)1e7 / n) * 2;i;i--){
		for(int j = 1;j <= n;j++)f[j][0] = f[j][1] = 0;
		u = (rand() + u) % n + 1;
		while(book[u]){u = (u + rand()) % n + 1;}
		book[u] = 1; dfs(u,0);
		if(ans <  max(f[u][0],f[u][1])){
			ans = max(f[u][0],f[u][1]);
			v = u;
		}
	}
	for(int i = head[v];i;i = e[i].nexte){
		u = e[i].to;
		if(!book[u]){
			for(int j = 1;j <= n;j++)f[j][0] = f[j][1] = 0;
			dfs(u,0); ans = max(f[u][0],max(ans,f[u][1]));
		}
	}
	printf("%lld\n",ans);
}
}
	return 0;
}
