#include<bits/stdc++.h>
using namespace std;

#define FO(name) freopen(name".in","r",stdin);freopen(name".out","w",stdout)

const int maxN = 1e5 + 10;

struct Edge {
	int to, val;
	Edge(int to, int val): to(to), val(val) {};
};

int A[maxN];
vector<Edge> G[maxN];
//bool vis[maxN];
set<int> cto[maxN];

inline void add_edge(int u, int v, int w) {
	G[u].push_back(Edge(v, w));
	G[v].push_back(Edge(u, w));
}

void dfs(int k, long long num, int p) {
	if (cto[k].size()){
//		cout << k << endl;
		for (auto i : cto[k]) {
			if (i == p) continue;
			cto[p].insert(i);
		}
//		return;
	}
		
	cto[p].insert(k);
//	vis[k] = true;
	num += A[k];
	for (auto e : G[k]) {
		if (cto[p].count(e.to) || (long long) e.val > num) continue;
		cto[p].insert(e.to);
		dfs(e.to, num - e.val, p);
	}
}

int main() {
	FO("transport");
	ios::sync_with_stdio(false);
	int N;
	int u, v, w;
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> A[i];
	for (int i = 1; i < N; i++) {
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}
	long long ans = 0;
	for (int i = 1; i <= N; i++) {
//		cto.clear();
//		for (int j = 1; j <= N; j++) vis[j] = 0;
		dfs(i, 0, i);
		ans += cto[i].size()-1;
//		cout << ans << " ";
	}
	cout << ans;
	return 0;
}
