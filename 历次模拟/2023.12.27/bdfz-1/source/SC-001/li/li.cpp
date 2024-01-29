#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<int> repr(n);
	iota(repr.begin(), repr.end(), 0);
	auto find = [&](int x) {
		while (x != repr[x]) {
			x = repr[x] = repr[repr[x]];
		}
		return x;
	};
	vector<pair<int, int>> edge(m);
	vector<vector<int>> adj(n);
	for (auto &[u, v] : edge) {
		cin >> u >> v;
		u--, v--;
		repr[find(u)] = find(v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> vc(n), ec(n);
	for (int i = 0; i < n; i++) {
		vc[find(i)]++;
	}
	for (auto [u, v] : edge) {
		ec[find(u)]++;
	}
	long long ans1 = 0, ans2 = 0;
	bool has_cyc = 0;
	vector<int> dep(n, -1);
	for (int i = 0; i < n; i++) {
		if (i != find(i)) continue;
		int len, max_deg = 0;
		auto dfs = [&](auto self, int u, int fa) -> void {
			max_deg = max<int>(max_deg, adj[u].size());
			for (int v : adj[u]) {
				if (v == fa) continue;
				if (dep[v] == -1) {
					dep[v] = dep[u] + 1;
					self(self, v, u);
				} else if (dep[u] > dep[v]) {
					len = dep[u] - dep[v] + 1;
				}
			}
		};
		dep[i] = 0;
		dfs(dfs, i, -1);
		if (vc[i] < ec[i]) {
			cout << "-1\n";
			exit(0);
		} else if (vc[i] == ec[i]) {
			has_cyc = 1;
			if (len != vc[i]) {
				cout << "-1\n";
				exit(0);
			} else {
				ans2 += len;
			}
		} else {
			if (max_deg > 3 || max_deg == 3 && ec[i] > 3) {
				cout << "-1\n";
				exit(0);
			} else if (max_deg == 3) {
				has_cyc = 1;
				ans2 += 3;
			} else {
				ans1 += 1LL * vc[i] * (vc[i] + 1) / 2;
			}
		}
	}
	if (has_cyc) {
		cout << "1 " << ans2 << "\n";
	} else {
		cout << "0 " << ans1 << "\n";
	}
	return 0;
}