# include <cstdio>

const int MAXN = 5e3 + 5;
const int MOD = 1e9 + 7;

int n, m;

int deg[MAXN << 1];

int C[MAXN][MAXN], cnt[MAXN << 1];

int main() {
	
  freopen("mondstadt.in", "r", stdin);
  freopen("mondstadt.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		++deg[x], ++deg[y];
	}
	for (int i = 0; i <= 5000; ++i) C[i][0] = 1;
	for (int i = 1; i <= 5000; ++i) {
		for (int j = 1; j <= i; ++j){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 2; j <= deg[i]; ++j) cnt[j] = (cnt[j] + C[ deg[i] ][j]) % MOD;
	}
	int ans = 0;
	for (int i = 2; i <= n; ++i) ans ^= cnt[i];
	printf("%d\n", ans);
	
	return 0;
}
