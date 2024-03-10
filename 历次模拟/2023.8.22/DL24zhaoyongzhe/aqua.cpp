#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0 , f  = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e7 + 10;
int n;

int head[maxn], tot;
struct edge{
	int to, nexte;
	edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int son[maxn], rt, ans = -1;
int lg[maxn << 1], dep[maxn];

void dfs(int u,int f){
//	printf("%d %d\n",u,f);
	int cnt = 1;
	for(int i = u;son[i];i = son[i]){cnt++;}
	int x = u;
	for(;son[x];x = son[x]){
		dep[x] = lg[cnt * 2 - 1] + 1 + dep[f];
//		ans = max(dep[x],ans);
		for(int i = head[x];i;i = e[i].nexte){
			int v = e[i].to;if(v == f || v == son[x])continue;
			dfs(v,x);
		}
	}
	dep[x] = lg[cnt * 2 - 1] + 1 + dep[f];
//	ans = max(dep[x],ans);
	for(int i = head[x];i;i = e[i].nexte){
		int v = e[i].to;if(v == f || v == son[x])continue;
		dfs(v,x);
	}
}

signed main(){
//	freopen("aqua.in","r",stdin);
//	freopen("aqua.out","w",stdout);
	n = read(); int u;
	for(int i = 1;i <= n;i++){
		u =  read();
		if(u) add(u, i);
		else rt = i;
	}
	lg[0] = -1;
	for(int i = 1;i <= n;i++){
		son[i] = read();
		lg[i] = lg[i >> 1] + 1;
	}
	dfs(rt, 0);
//	for(int i = 0;i <= n;i++)printf("dep[%d] = %d\n",i,dep[i]);
	for(int i = 1;i <= n;i++)ans = max(ans,dep[i]);
	printf("%lld\n",ans);
	return 0;
}
