#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

void Dijkstra(void); 

int n, k, N, S, T, id[15]; 
i64 d[4005], ans = 1e18; 
vector<pair<int, int>> G[4005]; 
inline void addedge(int u, int v, int w) {
	G[u].emplace_back(v, w); 
	G[v].emplace_back(u, w); 
}
struct Subway {
	int a[1005], b[1005], val; 
	int m, u[1005], v[1005], w[1005]; 
	void Read(int t) {
		for (int i = 1; i <= n; ++i) cin >> a[i]; 
		for (int i = 1; i <= n; ++i) cin >> b[i]; 
		cin >> m; 
		for (int i = 1; i <= m; ++i) cin >> u[i] >> v[i] >> w[i]; 
//		id[1] = t; Dijkstra(); 
//		val = d[n] - a[1]; 
	}
} a[10]; 
inline int cal(int i, int j) { return (j - 1) * n + i; }

bool vis[4005]; 
void Dijkstra(void) {
	#define pli pair<i64, int> 
	memset(d, 0x3f, sizeof d); memset(vis, 0, sizeof vis); 
	priority_queue<pli, vector<pli>, greater<pli> > q; 
//	for (int i = 1; i <= k; ++i) q.emplace(d[cal(1, i)] = a[id[i]].a[1], cal(1, i)); 
	q.emplace(d[1] = a[id[1]].a[1], 1); 
	while (!q.empty()) {
		auto tp = q.top(); q.pop(); 
		if (tp.first >= ans) return; 
		int u = tp.second; 
		if (vis[u]) continue; vis[u] = 1; 
		for (auto it : G[u]) {
			int v = it.first, w = it.second; 
			if (d[v] > d[u] + w) q.emplace(d[v] = d[u] + w, v); 
		}
	}
}

int main(void) {
	freopen("subway.in", "r", stdin); 
	freopen("subway.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n >> k; N = n * k; 
	for (int t = 1; t <= k; ++t) a[t].Read(t), id[t] = t; 
//	sort(a + 1, a + k + 1, [&](Subway x, Subway y) { return x.val < y.val; }); 
//	N = n * k; // swap(a[1], a[7]); 
	k = min(k, 6); 
	do {
		for (int i = 1; i <= N; ++i) G[i].clear(); 
		for (int op = 1; op <= k; ++op) {
			int i = id[op]; 
			for (int j = 1; j <= a[i].m; ++j)
				addedge(cal(a[i].u[j], op), cal(a[i].v[j], op), a[i].w[j]); 
		}
		for (int op = 1; op < k; ++op) {
			int u = id[op], v = id[op + 1]; 
			for (int i = 1; i <= n; ++i)
				G[cal(i, op)].emplace_back(cal(i, op + 1), a[u].b[i] + a[v].a[i]); 
		}
		Dijkstra(); 
		for (int op = 1; op <= k; ++op) ans = min(ans, d[cal(n, op)] + a[id[op]].b[n]); 
//		if (clock() / CLOCKS_PER_SEC > 1.9) break; 
	} while (next_permutation(id + 1, id + k + 1)); 
	cout << ans << "\n"; 
	return 0; 
} 
