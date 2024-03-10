#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 3007;
int f[MAXN][MAXN], a[MAXN][MAXN];
int vis[MAXN * MAXN];
int n, m, ans;
inline void read(int &temp) { cin >> temp; }
inline bool check(int x, int y, int k) {
	for (int i = 0; i < k; ++i)  if (f[x + i][y] < k - i)  return false;
	for (int i = 1; i < k; ++i)  if (f[x][y + i] < k - i)  return false;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < k; ++i) {
		if (vis[a[x + i][y]])  return false;
		++vis[a[x + i][y]];
	}
	for (int i = 1; i < k; ++i) {
		if (vis[a[x][y + i]])  return false;
		++vis[a[x][y + i]];
	}
	return true;
}
int main() {
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)  read(a[i][j]);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; i + k <= n && j + k <= m; ++k) {
				if (a[i][j] == a[i + k][j + k])  ++f[i][j];
				else  break;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 1; i + k - 1 <= n && j + k - 1 <= m; ++k)  ans += check(i, j, k);
	cout << ans << endl;
	return 0;
}
/*
3 3
1 3 4
2 0 3
5 2 1
*/
