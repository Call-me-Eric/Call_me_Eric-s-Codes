// how V-BCC? /kk

#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>
#include <map>

using pii = std::pair<int, int>;
const int N = 1e6;
const int M = 2e6;

int n, m; std::vector<int> g[N + 5];

int dfn[N + 5], low[N + 5], cid;
int bct, bel[N + 5];
int st[N + 5], tp, inst[N + 5];
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++cid;
	st[++tp] = u, inst[u] = true;
	for(int v : g[u]) {
		if(v == fa) continue;
		if(!dfn[v]) {
			tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
		} else if(inst[v]) {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		bct++;
		while(true) {
			int x = st[tp--];
			inst[x] = false;
			bel[x] = bct;
			if(x == u) break;
		}
	}
}

std::vector<int> wei[N + 5];
std::map<pii, int> e;

int main() {
	freopen("inazuma.in", "r", stdin), freopen("inazuma.out", "w", stdout);

//	freopen("a.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		if(u > v) std::swap(u, v);
		e[ {u, v}] += w;
		g[u].push_back(v), g[v].push_back(u);
	}
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) tarjan(i, i);
	}
	int ans = 1e9;
	for(auto k : e) {
		int u = k.first.first, v = k.first.second, w = k.second;
		if(bel[u] != bel[v]) ans = std::min(ans, w);
		else wei[bel[u]].push_back(w);
	}
	for(int i = 1; i <= bct; i++) {
		if(!wei[i].size()) continue;
		assert(wei[i].size() >= 3);
		std::sort(wei[i].begin(), wei[i].end());
		int t = wei[i][0] + wei[i][1];
		for(int j = 2, li = wei[i].size(); j < li; j++) {
			t = std::min(t, wei[i][j]);
		}
		ans = std::min(ans, t);
	}
	printf("%d\n", ans);
	return 0;
}
