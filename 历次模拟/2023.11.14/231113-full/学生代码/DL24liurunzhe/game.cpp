# include <cstdio>
# include <algorithm>

# define int long long

constexpr int MAXN = 2e5 + 5;

int n;

int L, R;

int a[MAXN << 1];

signed main() {
	
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	
	scanf("%lld %lld %lld", &n, &L, &R);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; ++i) sum1 += i & 1 ? a[i] : 0, sum2 += ~i & 1 ? a[i] : 0;
	puts(sum1 < L || sum2 > R ? "Alice" : "Bob");
	
	return 0;
}
