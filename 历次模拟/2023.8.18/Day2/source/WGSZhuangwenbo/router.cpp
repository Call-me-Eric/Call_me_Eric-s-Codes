#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using i64 = long long;

const int N = 1e6;

int n, a[N + 5];
std::vector<int> g[N + 5];

i64 f[N + 5][3];
void dfs(int u, int fa) {
	f[u][0] = a[u], f[u][2] = 0;
	int ct = 0;
	for(int v : g[u]) ct += v != fa;
	if(ct) f[u][1] = 0;
	for(int v : g[u]) {
		if(v == fa) continue;
		dfs(v, u);
		f[u][0] += std::min({f[v][0], f[v][1], f[v][2]});
		f[u][1] += f[v][0];
		f[u][2] += std::min({f[v][0], f[v][1]});
	}
}

int main() {
	freopen("router.in", "r", stdin), freopen("router.out", "w", stdout);

	n = rd(); for(int i = 1; i <= n; i++) a[i] = rd();
	for(int i = 2; i <= n; i++) {
		int u = rd(), v = rd();
		g[u].push_back(v), g[v].push_back(u);
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 3; j++) f[i][j] = 2e9;
	}
	dfs(1, 1);

	printf("%lld\n", std::min(f[1][0], f[1][1]));
	return 0;
}
/*
4
1 10000 10000 1
1 2
2 3
3 4

4
1000 1 1 1000
1 2
2 3
3 4
*/
