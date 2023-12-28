#include <bits/stdc++.h>
using namespace std;

const int N = 260, M = 3.2e4;
int r, g, b, n, m, idx, len, fa[M], dfn[M], trans[M], suf[3][M];
unordered_map <char, int> got; bool vis[N][N][N];
struct Edge { int u, v, col; } e[M];
struct Node { int pos, num[3]; bitset <M> sta; };
vector <int> gr[M]; vector <pair <int, int> > gra[M];

inline int getf(int x) {
	return fa[x] == x? x : fa[x] = getf(fa[x]);
}

inline void dfs(int cur, int f) {
	trans[dfn[cur] = ++idx] = cur;
	for (auto to: gr[cur]) if (to ^ f) dfs(to, cur);
}

int main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> r >> g >> b >> m, n = r + g + b + 1;
	got['r'] = 0, got['g'] = 1, got['b'] = 2;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		char col; cin >> e[i].u >> e[i].v >> col;
		e[i].col = got[col]; int fu = getf(e[i].u), fv = getf(e[i].v);
		if (fu ^ fv) fa[fu] = fv, gr[e[i].u].push_back(e[i].v), gr[e[i].v].push_back(e[i].u);
	}
	dfs(1, 1);
	for (int i = 1; i <= m; ++i) {
		if (dfn[e[i].u] > dfn[e[i].v]) swap(e[i].u, e[i].v);
		gra[e[i].v].push_back({i, e[i].col});
	}
	for (int i = n; i >= 1; --i) {
		for (auto it: gra[trans[i]]) suf[it.second][i] = 1;
		for (int j = 0; j < 3; ++j) suf[j][i] += suf[j][i + 1];
	}
	queue <Node> q; Node beg; beg.pos = 1; q.push(beg);
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		int pos = cur.pos, num[3];
		for (int i = 0; i < 3; ++i) num[i] = cur.num[i];
		if (num[0] == r && num[1] == g && num[2] == b) {
			cout << "YES" << endl;
			for (int i = 1; i <= m; ++i) cout << cur.sta[i];
			return 0;
		}
		if (vis[pos][num[0]][num[1]]) continue;
		vis[pos][num[0]][num[1]] = true;
		int rMax = num[0] + suf[0][pos + 1];
		int gMax = num[1] + suf[1][pos + 1];
		int bMax = num[2] + suf[2][pos + 1];
		if (rMax < r || gMax < g || bMax < b) continue;
		if (num[0] > r || num[1] > g || num[2] > b) continue;
		for (auto it: gra[trans[pos + 1]]) {
			int id = it.first, col = it.second;
			cur.sta[id] = true, ++cur.pos, ++cur.num[col];
			q.push(cur);
			cur.sta[id] = false, --cur.pos, --cur.num[col];
		}
	}
	cout << "NO" << endl;
	return 0;
}
