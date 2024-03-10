#include<bits/stdc++.h>
#include<unordered_map>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
const int mpcol[3] = {114514191, 998244353, -114514191 - 998244353};
int n, col[maxn];
int val[maxn], s[maxn];
char str[maxn];

int head[maxn], tot;
struct edge{
	int to, nexte;
	edge(int t = 0,int ne = 0):to(t),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int idx, dfn[maxn], fa[maxn];
int ans = 0;
void dfs(int u,int f){
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f)continue;
		dfn[v] = ++idx;
		s[dfn[v]] = s[dfn[u]] + val[v];
		dfs(v,u);fa[v] = u;
	}
}
unordered_map<int,int> mp;
bool book[maxn];
int siz[maxn], son[maxn], sum, rt;
void getroot(int u,int f){
	siz[u] = 1;son[u] = 0;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f || book[v])continue;
		getroot(v,u);
		siz[u] += siz[v];
		son[u] = siz[v] > son[u] ? siz[v] : son[u];
	}
	son[u] = max(son[u],sum - son[u]);
	if(son[u] < son[rt])rt = u;
}
void dfs1(int u,int f){
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;if(v == f)continue;
	}
}

signed main(){
	n = read();int u, v;
	scanf("%s",str + 1);
	for(int i = 1;i <= n;i++){col[i] = str[i] - 'a';val[i] = mpcol[col[i]];}
	for(int i = 1;i < n;i++){
		u = read(); v = read();
		add(u, v);add(v, u);
	}
	dfn[1] = ++idx;
	s[1] = val[1]; dfs(1, 0);
	printf("%lld\n",ans);
	return 0;
}

