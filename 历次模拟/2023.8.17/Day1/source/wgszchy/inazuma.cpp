#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-2;
const int N = 4e6 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 1e9 + 7;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, m;
struct node {
	int v, nt, d;
} e[N];
int head[N], tot = 1;
void add(int u, int v, int d) {
	e[++tot] = {v, head[u], d};
	head[u] = tot;
}
int cut[N];
int dfn[N], low[N], id;
int ans = INT_MAX;
void tarjan(int u, int ine) {
	dfn[u] = low[u] = ++id;
	for(int i = head[u]; i; i = e[i].nt) {
		int v = e[i].v;
		if(!dfn[v]) {
			tarjan(v, i);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) cut[i] = cut[i ^ 1] = 1, ans = min(ans, e[i].d);
		} else if(i != (ine ^ 1)) low[u] = min(low[u], dfn[v]);
	}
}
int scnt, bel[N];
vector<int>U[N];
void dfs(int u, int col) {
	bel[u] = col;
	U[col].push_back(u);
	for(int i = head[u]; i; i = e[i].nt) {
		int v = e[i].v;
		if(bel[v] || cut[i]) continue;
		dfs(v, col);
	}
}
int P[N];
struct L {
	int u, v, d;
	bool operator<(L t)const {
		return u == t.u ? v < t.v : u < t.u;
	}
} edge[N];
signed main() {
	freopen("inazuma.in", "r", stdin);
	freopen("inazuma.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		int u, v, d;
		u = read(), v = read(), d = read();
		edge[i] = {u, v, d};
		P[u] += d, P[v] += d;
	}
	sort(edge + 1, edge + 1 + m);
	for(int i = 1; i <= m; i++) {
		int totd = edge[i].d;
		while(edge[i].u == edge[i + 1].u && edge[i].v == edge[i + 1].v) {
			totd += edge[i + 1].d;
			i++;
		}
		add(edge[i].u, edge[i].v, totd), add(edge[i].v, edge[i].u, totd);
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, 0);
	for(int i = 1; i <= n; i++) if(!bel[i]) dfs(i, ++scnt);
	for(int i = 1; i <= scnt; i++) {
		int res = INT_MAX;;
		for(int j = 0; j < U[i].size(); j++) res = min(res, P[U[i][j]]);
		ans = min(ans, res);
	}
	printf("%lld\n", ans);
	return 0;
}

