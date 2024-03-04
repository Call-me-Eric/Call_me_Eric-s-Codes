#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN = 3000007;
constexpr int mod = 1000000007;
int fct[MAXN], bsk[MAXN], deg[MAXN], cnt[MAXN];
int n, m, ans;
inline void read(int &temp) { cin >> temp; }
inline int ksm(int base, int k) {
	int res = 1;
	while (k) {
		if (k & 1)  res = res * base % mod;
		base = base * base % mod, k >>= 1;
	}
	return res;
}
inline int C(int m, int n) { return fct[n] * ksm(fct[m] * fct[n - m] % mod, mod - 2) % mod; }
signed main() {
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m);
	fct[0] = 1;
	for (int i = 1; i <= n; ++i)  fct[i] = fct[i - 1] * i % mod;
	for (int i = 1, u, v; i <= m; ++i) {
		read(u), read(v), --bsk[deg[u]], --bsk[deg[v]], ++bsk[++deg[u]], ++bsk[++deg[v]];
	}
	for (int i = 2; i < n; ++i) {
		if (!bsk[i])  continue;
		cnt[i] += bsk[i];
		for (int j = 2; j < i; ++j)  cnt[j] += C(j, i) * bsk[i] % mod, cnt[j] %= mod;
	}
	for (int i = 2; i < n; ++i)  ans ^= cnt[i];
	cout << ans << endl;
	return 0;
}
/*
4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/
