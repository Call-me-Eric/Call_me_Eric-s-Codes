#include <iostream>
#include <vector>
#define int long long
using namespace std;
constexpr int MAXN(2007);
constexpr int mod(998244353);
vector <int> e[MAXN];
int f[MAXN][MAXN];
int g[MAXN], a[MAXN];
int n, k;
inline void read(int &temp) { cin >> temp; }
void dfs(int u, int fa) {
	for (auto v : e[u]) {
		if (v == fa)  continue;
		dfs(v, u);
	}
	for (int i(1); i <= k; ++i) {
		if (a[u] && a[u] != i)  continue;
		f[u][i] = 1;
		for (auto v : e[u]) {
			if (v == fa)  continue;
			f[u][i] = f[u][i] * (((g[v] - f[v][i]) % mod + mod) % mod) % mod;
		}
		g[u] = (g[u] + f[u][i]) % mod;
	}
}
signed main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(k);
	for (int i(1); i <= n; ++i)  read(a[i]);
	for (int i(1), u, v; i < n; ++i)  read(u), read(v), e[u].push_back(v), e[v].push_back(u);
	dfs(1, 0);
	cout << g[1] << endl;
	return 0;
}
