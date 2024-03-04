#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN = 1000007;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN], ans[MAXN];
int n, m;
inline void read(int &temp) { cin >> temp; }
inline bool ifg(int A, int B, int C, int D) {
	if (A < C || B < D)  return false;
	if (A == C && B == D)  return true;
	if (B > D && (B - D) % A == 0 && A == C)  return true;
	if (A > C && (A - C) % B == 0 && B == D)  return true;
	return ifg(A - B, B, C, D) || ifg(A, B - A, C, D);
}
signed main() {
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m);
	for (int i = 1; i <= n; ++i)  read(a[i]), read(b[i]);
	for (int i = 1; i <= m; ++i)  read(c[i]), read(d[i]);
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)  ans[i] += ifg(a[j], b[j], c[i], d[i]);
	for (int i = 1; i <= m; ++i)  cout << ans[i] << endl;
	return 0;
}
/*
3 4
6 9
5 3
1 1
6 3
1 2
2 1
5 3
*/

