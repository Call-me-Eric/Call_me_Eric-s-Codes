# include <cstdio>
# include <cmath>
# include <ctime>
# include <random>
# include <algorithm>

std::mt19937 Gen(time(nullptr) ^ std::random_device()());

int n, m, q;

int ans[3000233];

int main() {
	
	freopen("approx.in", "r", stdin);
	freopen("approx.out", "w", stdout);
	
	scanf("%d %d %d", &n, &m, &q);
	double x = log2(m);
	for (int i = 1; i <= q; ++i) ans[i] = int(log2(i) * m / x);
	std::shuffle(ans + 5, ans + q + 1, Gen);
	for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	
	return 0;
}
