#include <bits/stdc++.h>
using namespace std;
using arr = array<int, 3>;
constexpr int N = 260, M = N * N, inf = 1e9;
arr cnt;
int n, m;
struct edge {
	int u, v, w;
}e[M];
int use[M], iss[M], ist[M], dis[M], pre[M];
vector<int> G[M];
struct dsu_t {
	int fa[N];
	int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
	void clear() {
		iota(fa + 1, fa + n + 1, 1);
	}
	bool merge(int u, int v) {
		u = find(u), v = find(v);
		if(u != v) return fa[u] = v, 1;
		else return 0;
	}
}dsu;
int main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(0);
	for(auto &x : cnt) cin >> x, n += x;
	n += 1;
	cin >> m;
	for(int i = 1; i <= m; i ++) {
		char ch;
		cin >> e[i].u >> e[i].v >> ch;
		e[i].w = (ch == 'r' ? 0 : ch == 'g' ? 1 : 2);
	}
	while(1) {
		dsu.clear();
		arr cur{};
		for(int i = 1; i <= m; i ++) {
			if(use[i]) {
				assert(dsu.merge(e[i].u, e[i].v));
				cur[e[i].w] ++;
			}
		}
		int flag = 0;
		for(int i = 1; i <= m; i ++) if(!use[i]) {
			iss[i] = cur[e[i].w] < cnt[e[i].w];
			ist[i] = dsu.find(e[i].v) != dsu.find(e[i].u);
			if(iss[i] && ist[i]) {
				flag = 1;
				use[i] = 1;
				break;
			}
		}
		if(flag) continue;
		vector<int> vec;
		for(int i = 1; i <= m; i ++) if(use[i]) vec.emplace_back(i);
		for(int i = 1; i <= m; i ++) G[i].clear();
		for(auto i : vec) {
			dsu.clear();
			for(auto j : vec) if(i != j) dsu.merge(e[j].u, e[j].v);
			cur[e[i].w] --;
			for(int j = 1; j <= m; j ++) if(!use[j]) {
				if(dsu.find(e[j].u) != dsu.find(e[j].v)) {
					G[j].emplace_back(i);
				}
				if(cur[e[j].w] < cnt[e[j].w]) {
					G[i].emplace_back(j);
				}
			}
			cur[e[i].w] ++;
		}
		auto bfs = [&] {
			queue<int> q;
			fill(dis + 1, dis + m + 1, inf);
			for(int i = 1; i <= m; i ++) if(!use[i]) {
				if(iss[i]) q.emplace(i), dis[i] = 0, pre[i] = 0;
			}
			while(!q.empty()) {
				int u = q.front(); q.pop();
				for(auto v : G[u]) {
					if(dis[v] > dis[u] + 1) {
						dis[v] = dis[u] + 1;
						pre[v] = u;
						if(!use[v] && ist[v]) {
							return v;
						}
						q.emplace(v);
					}
				}
			}
			return -1;
		};
		int x = bfs();
		if(x == -1) break;
		for(; x; x = pre[x]) use[x] ^= 1;
	}
	int sum = accumulate(use + 1, use + m + 1, 0);
	if(sum == n - 1) {
		cout << "YES\n";
		dsu.clear();
		arr cur{};
		for(int i = 1; i <= m; i ++) {
			cout << use[i];
			if(use[i]) assert(dsu.merge(e[i].u, e[i].v)), cur[e[i].w] ++;
		}
		assert(cur[0] == cnt[0] && cur[1] == cnt[1] && cur[2] == cnt[2]);
	} else {
		cout << "NO\n";
	}
    return 0;
}