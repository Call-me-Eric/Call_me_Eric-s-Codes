#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e6 + 5;

queue<int> q;
vector<int> mp[N];
struct Edge {
	int to;
	int nxt;
} e[N];

int head[N], dfn[N], low[N], scc[N], sz[N], id[N], od[N];
int stk[N], top;

int n, m, tot, dfn_cnt, scc_cnt;
int f[N], g[N], f_cnt[N], ans;
bool flg[N];

inline void add(int u, int v) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}

inline void tarjan(int u) {
	dfn[u] = ++dfn_cnt, low[u] = dfn_cnt;
	stk[top++] = u;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (!scc[v]) low[u] = min(low[u], dfn[v]);
	}
	
	if (dfn[u] == low[u]) {
		++scc_cnt;
		while (true) {
			scc[stk[top - 1]] = scc_cnt;
			--top, ++sz[scc_cnt];
			if (stk[top] == u || top == 0) break;
		}
		
	}
}

int main() {
	freopen("goood.in", "r", stdin);
	freopen("goood.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d %d", &u, &v);
		add(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int u = 1; u <= n; ++u) {
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (scc[u] == scc[v]) continue;
			mp[scc[u]].push_back(scc[v]);
		}
	}
	for (int u = 1; u <= scc_cnt; ++u) {
		sort(mp[u].begin(), mp[u].end());
		mp[u].erase(unique(mp[u].begin(), mp[u].end()), mp[u].end());
		for (auto v : mp[u]) ++id[v], ++od[u];
	}
	for (int u = 1; u <= scc_cnt; ++u) {
		if (id[u] + od[u] == 0) {
			printf("0\n");
			return 0;
		}
	}
	int cnt = 0;
	for (int u = 1; u <= scc_cnt; ++u)
		if (id[u] == 0) q.push(u);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto v : mp[u]) {
			--id[v];
			if (f[v] == f[u] + 1) ++g[v];
			else f[v] = max(f[v], f[u] + 1), g[v] = 1;
			if (id[v] == 0) q.push(v);
		}
	}
	for (int i = 1; i <= scc_cnt; ++i) ++f_cnt[f[i]];
	for (int i = 1; i <= scc_cnt; ++i) {
		if (g[i] == f_cnt[f[i] - 1] && f_cnt[f[i]] == 1) {
			ans += sz[i];
			flg[i] = true;
		}	
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i)
		if(flg[scc[i]]) printf("%d ", i);
	printf("\n");
	fclose(stdin), fclose(stdout);
	return 0;
}

