#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; i++) {
			fa[i] = i;
		}
	}
	int getfa(int v) {
		return (fa[v] == v) ? v : (fa[v] = getfa(fa[v]));
	}
	bool merge(int u, int v) {
		u = getfa(u), v = getfa(v);
		if (u == v) {
			return false;
		}
		fa[u] = v;
		return true;
	}
	bool same(int u, int v) {
		return getfa(u) == getfa(v);
	}
};

bool merge(int n, vector<int> &l, DSU &dsu) {
	for (int i = 0; i < n * 2 - 1; i++) {
		if (l[i] % 2 == i % 2) {
			return false;
		}
		if (i - l[i] >= 0 && i + l[i] < n * 2 - 1) {
			++l[i];
		}
		if (i - l[i] < -1 || i + l[i] >= n * 2) {
			return false;
		}
	}
	for (int i = 0, mid = -1, len = -1; i < n * 2 - 1; i++) {
		int nxt = 0;
		if (mid + len > i) {
			nxt = min(mid + len - i, l[mid * 2 - i]);
			if (l[i] < nxt) {
				return false;
			}
		}
		while (nxt < l[i]) {
			if ((i - nxt) % 2 == 0) {
				dsu.merge((i - nxt) / 2, (i + nxt) / 2);
			}
			++nxt;
		}
		if (i + l[i] > mid + len) {
			mid = i, len = l[i];
		}
	}
	return true;
}

struct Graph {
	int n;
	vector<vector<pair<int, int>>> e;
	vector<int> deg;
	void addedge(int a, int b, int c) {
		e[a].emplace_back(b, c), ++deg[b];
	}
	Graph(int tot) : n(tot), e(n), deg(n) {}
	int scc, dfc;
	vector<int> dfn, low, col;
	vector<bool> ins;
	stack<int> stk;
	bool solve() {
		scc = -1, dfc = 0;
		dfn.resize(n, 0);
		low.resize(n, 0);
		col.resize(n, -1);
		ins.resize(n, 0);
		for (int i = 0; i < n; i++) {
			if (!dfn[i]) {
				tarjan(i);
			}
		}
		Graph g(scc + 1);
		for (int v = 0; v < n; v++) {
			for (auto [u, w] : e[v]) {
				if (col[u] != col[v]) {
					g.addedge(col[v], col[u], w);
				} else if (col[u] == col[v] && w > 0) {
					return false;
				}
			}
		}
		g.solve_dag();
		ans.resize(n, 0);
		for (int i = 0; i < n; i++) {
			if (g.ans[col[i]] >= 26) {
				return false;
			}
			ans[i] = g.ans[col[i]];
		}
		return true;
	}
	void tarjan(int v) {
		dfn[v] = low[v] = ++dfc;
		ins[v] = true, stk.push(v);
		for (auto [u, w] : e[v]) {
			if (!dfn[u]) {
				tarjan(u);
				low[v] = min(low[v], low[u]);
			} else if (ins[u]) {
				low[v] = min(low[v], dfn[u]);
			}
		}
		if (low[v] == dfn[v]) {
			for (++scc; stk.top() != v; stk.pop()) {
				col[stk.top()] = scc, ins[stk.top()] = false;
			}
			col[v] = scc, ins[v] = false, stk.pop();
		}
	}
	vector<int> ans;
	void solve_dag() {
		ans.resize(n, 0);
		queue<int> que;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				que.push(i);
			}
		}
		while (!que.empty()) {
			int v = que.front();
			que.pop();
			for (auto [u, w] : e[v]) {
				ans[u] = max(ans[u], ans[v] + w);
				if (!--deg[u]) {
					que.push(u);
				}
			}
		}
	}
};

bool solve(int tid) {
	int n;
	cin >> n;
	vector<int> sa(n), rk(n);
	for (int i = 0; i < n; i++) {
		cin >> sa[i], rk[sa[i]] = i;
	}
	vector<int> len(n * 2 - 1);
	for (int i = 0; i < n * 2 - 1; i++) {
		cin >> len[i];
	}
	DSU dsu(n);
	if (!merge(n, len, dsu)) {
		return false;
	}
	Graph g(n);
	for (int i = 0; i < n * 2 - 1; i++) {
		int u = i - len[i], v = i + len[i];
		if (0 <= u && u < n * 2 - 1 && 0 <= v && v < n * 2 - 1 && u % 2 == 0) {
			u /= 2, v /= 2;
			if (dsu.same(u, v)) {
				return false;
			}
			if (rk[u] < rk[v]) {
				g.addedge(dsu.getfa(u), dsu.getfa(v), 1);
			} else {
				g.addedge(dsu.getfa(v), dsu.getfa(u), 1);
			}
		}
	}
	for (int i = 1; i < n; i++) {
		int u = sa[i - 1], v = sa[i];
		int ru = (u + 1 < n) ? rk[u + 1] : -1;
		int rv = (v + 1 < n) ? rk[v + 1] : -1;
		g.addedge(dsu.getfa(u), dsu.getfa(v), ru < rv ? 0 : 1);
	}
	if (!g.solve()) {
		return false;
	}
	string s(n, 'a');
	for (int i = 0; i < n; i++) {
		s[i] = g.ans[dsu.getfa(i)] + 'a';
	}
	printf("%s\n",s.c_str());
	return true;
}

int main() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		if (!solve(t)) {
			printf("-1\n");
		}
	}
	return 0;
}
