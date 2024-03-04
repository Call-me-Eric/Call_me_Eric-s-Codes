# include <cstdio>
# include <algorithm>

using std::swap;

# define int long long

constexpr int MAXN = 100;
constexpr int MOD = 998244353;

int n, m;

int p[MAXN << 1];

int cnt[MAXN << 1], tot;

void dfs(int x) {
	if (x > m) {
		++tot;
		int res = 0;
		for (int i = 1; i <= n; ++i) if (p[i] != i) ++res;
		++cnt[res];
		return;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			swap(p[i], p[j]), dfs(x + 1), swap(p[i], p[j]);
	}
}

int fpow(int x, int k, int MOD) {
	int res = 1;
	for (; k; k >>= 1) {
		if (k & 1) res = 1LL * res * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return res;
}

signed main() {
	
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	
	int T;
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld %lld", &n, &m);
		for (int i = 1; i <= n; ++i) p[i] = i;
		for (int i = 0; i <= n; ++i) cnt[i] = 0; tot = 0;
		dfs(m);
		int ans = 0;
		int inv = fpow(tot, MOD - 2, MOD);
		for (int i = 0; i <= n; ++i) {
			ans += 1LL * cnt[i] % MOD * i % MOD;
			if (ans >= MOD) ans -= MOD;
		}
		printf("%lld\n", ans * inv % MOD);
	}
	
	return 0;
}
