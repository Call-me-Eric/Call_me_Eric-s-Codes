#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int main() {
	// freopen("tree.in", "r", stdin);
	// freopen("tree.out", "w", stdout);
	cin.tie(nullptr)->sync_with_stdio(0);

	int T;
	cin >> T;

	while (T--) {
		int n;
		cin >> n;

		vector<vector<int>> G(n);
		for (int i = 0 ; i < n - 1 ; i++) {
			static int u , v;
			cin >> u >> v;
			--u , --v;
			G[u].push_back(v);
			G[v].push_back(u);
		}

		// min leaf
		int root = -1;
		for (int i = 0 ; i < n ; i++) {
			if (G[i].size() == 1) {
				root = i;
				break;
			}
		}
		assert(root != -1);

		vector<int> mn(n);
		auto dfs1 = [&](auto self , int u , int fa) -> void {
			mn[u] = G[u].size() == 1 ? u : INT_MAX;
			for (int v : G[u]) {
				if (v == fa) continue;
				self(self , v , u);
				mn[u] = min(mn[u] , mn[v]);
			}
		};
		dfs1(dfs1 , root , -1);

		// find max root
		auto dfs2 = [&](auto self , int u , int fa) -> int {
			int p = -1;
			for (int v : G[u]) {
				if (v == fa) continue;
				if (p == -1 || mn[v] > mn[p]) {
					p = v;
				}
			}
			if (p == -1 || u > mn[p]) return u;
			return self(self , p , u);
		};
		root = dfs2(dfs2 , root , -1);
		dfs1(dfs1 , root , -1);

		vector<int> Ans;
		auto dfs3 = [&](auto self , int u , int fa) -> void {
			sort(G[u].begin() , G[u].end() , [&](int x , int y) { return mn[x] < mn[y]; });
			for (int v : G[u]) {
				if (v == fa) continue;
				self(self , v , u);
			}
			Ans.push_back(u);
		};
		dfs3(dfs3 , root , -1);

		assert(Ans.size() == n);
		for (int i = 0 ; i < n ; i++) {
			cout << Ans[i] + 1 << " \n"[i == n - 1];
		}
	}

	return 0;
}