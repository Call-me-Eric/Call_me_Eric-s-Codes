#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 2e5 + 5;

int n, m;
vector<pair<int, int>> adj[N];
vector<int> bdj[N];
bool vis[N], ok, era[N];
int ind[N];
ll ans;
int cnt;

inline void dfs(int u) {
	vis[u] = 1;
	++cnt;
	if(adj[u].size() == 3) {
		if(ok) {
			cout << -1 << "\n";
			exit(0);
		}
		ok = 1;
	}
	for(auto e : adj[u]) {
		int v = e.first;
		if(!vis[v]) dfs(v);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
	}
	rep(i, 1, n) if(adj[i].size() >= 4) {
		cout << -1 << "\n";
		return 0;
	}
	rep(i, 1, n) if(!vis[i]) cnt = 0, ok = 0, dfs(i), ans += 1ll * cnt * (cnt+1) / 2;
	rep(u, 1, n) for(int i = 0; i < adj[u].size(); ++i) for(int j = 0; j < i; ++j) {
		bdj[adj[u][i].second].push_back(adj[u][j].second);
		bdj[adj[u][j].second].push_back(adj[u][i].second);
	}
	rep(i, 1, m) if(bdj[i].size() >= 4) {
		cout << -1 << "\n";
		return 0;
	}
	rep(i, 1, m) ind[i] = bdj[i].size();
	queue<int> que;
	rep(i, 1, m) if(ind[i] <= 1) que.push(i);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		era[u] = 1;
		for(int v : bdj[u]) if(--ind[v] == 1) que.push(v);
	}
	rep(i, 1, m) if(!era[i] && bdj[i].size() == 3) {
		cout << -1 << "\n";
		return 0;
	}
	int cnt = 0;
	rep(i, 1, m) cnt += !era[i];
	if(cnt) {
		cout << 1 << " " << cnt << "\n";
	} else {
		cout << 0 << " " << ans << "\n";
	}

	return 0;
}
