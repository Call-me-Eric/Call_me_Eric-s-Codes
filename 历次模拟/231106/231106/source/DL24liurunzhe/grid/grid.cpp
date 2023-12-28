# include <cstdio>

# define int long long

constexpr int MAXN = 500 + 5, MOD = 998244353;

int n, m;

int a[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN];

int dir[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int solve(int x, int y) {
	if (f[x][y]) return f[x][y];
	f[x][y] = 1;
	for (int k = 0; k < 4; ++k) {
		int nx = x + dir[k][0], ny = y + dir[k][1];
		if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
			if (a[x][y] < a[nx][ny]) 
				f[x][y] = (f[x][y] + solve(nx, ny)) % MOD;
			else f[x][y] = (f[x][y] + 1) % MOD;
		}
	}
	return f[x][y];
}

int solve2(int x, int y) {
	if (g[x][y]) return g[x][y];
	g[x][y] = 1;
	for (int k = 0; k < 4; ++k) {
		int nx = x + dir[k][0], ny = y + dir[k][1];
		if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && a[x][y] > a[nx][ny]) {
			g[x][y] = (g[x][y] + solve2(nx, ny)) % MOD;
		}
	}
	return g[x][y];
}

signed main() {
	
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) scanf("%lld", &a[i][j]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) 
			f[i][j] = solve(i, j), ans = (ans + f[i][j]) % MOD;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) g[i][j] = solve2(i, j);
	}
	scanf("%lld", &m);
	for (int q = 1; q <= m; ++q) {
		int x, y;
		scanf("%lld %lld", &x, &y);
		printf("%lld\n", (ans - (f[x][y] - 1) * g[x][y] % MOD + MOD) % MOD);
	}
	
	return 0;
}
