# include <cstdio>
# include <vector>

# define int long long

constexpr int MAXN = 1e3 + 5, MOD = 998244353;

int n, m, cnt;

int a[MAXN << 1], mp[MAXN];

std::vector<int> G[MAXN << 1];

int f[MAXN][MAXN], sum[MAXN];

void dfs(int u, int father) {
	for (int k : G[u]) if (k != father) {
		dfs(k, u);
	}
	if (a[u]) {
		f[u][ a[u] ] = 1;
		for (int k : G[u]) if (k != father) 
			f[u][ a[u] ] = f[u][ a[u] ] * (sum[k] - f[k][ a[u] ] + MOD) % MOD;
	}
	else {
		for (int i = 1; i <= cnt + 1; ++i) {
			f[u][i] = 1;
			for (int k : G[u]) if (k != father)
				f[u][i] = f[u][i] * (sum[k] - f[k][i] + MOD) % MOD;
		}
	}
	sum[u] = f[u][cnt + 1] * (m - cnt) % MOD;
	for (int i = 1; i <= cnt; ++i) sum[u] = (sum[u] + f[u][i]) % MOD;
}

signed main() {
	
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	
	scanf("%lld %lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		if (a[i]) {
			if (!mp[ a[i] ]) mp[ a[i] ] = ++cnt;
			a[i] = mp[ a[i] ];
		}
	}
	for (int i = 1; i < n; ++i) {
		int x, y; scanf("%lld %lld", &x, &y);
		G[x].push_back(y), G[y].push_back(x);
	}
	dfs(1, 0);
	printf("%lld\n", sum[1]);
	
	return 0;
}
