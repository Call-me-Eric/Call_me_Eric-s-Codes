#include <iostream>
#include <vector>
#define int long long
using namespace std;
constexpr int MAXN = 1000007;
constexpr int INF = 0x3f3f3f3f3f3f3f3f;
int f[MAXN][7];
int a[MAXN];
int n;
vector <int> e[MAXN];
inline void read(int &temp) { cin >> temp; }
void dfs(int u, int fa) {
	if (!e[u].size() && u == 1)  f[u][2] = INF;
	if (e[u].size() == 1 && u != 1)  f[u][2] = INF;
	for (auto v : e[u]) {
		if (v == fa)  continue;
		dfs(v, u);
		f[u][0] += min(f[v][1], f[v][2]), f[u][1] += min(f[v][0], min(f[v][1], f[v][2])), f[u][2] += f[v][1];
	}
	f[u][1] += a[u];
}
signed main() {
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i = 1; i <= n; ++i)  read(a[i]);
	for (int i = 1, u, v; i < n; ++i)  read(u), read(v), e[u].push_back(v), e[v].push_back(u);
	dfs(1, 0);
	cout << min(f[1][1], f[1][2]) << endl;
	return 0;
}
/*
4
1 17 13 4
1 2
1 3
3 4
*/
