#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1007;
constexpr int INF = 0x3f3f3f3f;
int a[MAXN][MAXN], b[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
int n, ans1, ans2, k, zz;
inline void read(int &temp) { cin >> temp; }
void dfs(int line, int p) {
	if (!line)  return ;
	b[line][p] = -INF;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)  g[i][j] = max(max(g[i - 1][j - 1], g[i - 1][j]) + b[i][j], -INF);
	for (int i = 1; i <= n; ++i)  if (g[n][i] > ans2)  ans2 = g[n][i];
	b[line][p] = a[line][p];
	if (f[line - 1][p - 1] > f[line - 1][p])  dfs(line - 1, p - 1);
	else  dfs(line - 1, p);
}
int main() {
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)  read(a[i][j]), b[i][j] = a[i][j];
	memset(f, -0x3f, sizeof(f));
	memset(g, -0x3f, sizeof(g));
	f[0][0] = 0, g[0][0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)  f[i][j] = max(max(f[i - 1][j - 1], f[i - 1][j]) + a[i][j], -INF);
	for (int i = 1; i <= n; ++i)  if (f[n][i] > ans1)  ans1 = f[n][i], zz = i;
	if (k != 2)  return cout << ans1 << endl, 0;
	dfs(n, zz);
	cout << ans2 << endl;
	return 0;
}
/*
3 2
1
2 3
3 3 1


*/
