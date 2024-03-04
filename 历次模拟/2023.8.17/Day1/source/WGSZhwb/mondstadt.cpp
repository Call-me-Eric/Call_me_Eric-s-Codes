#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

using i64 = long long;
const i64 P = 1e9 + 7;

const int N = 1e6;

i64 fpow(i64 b, i64 p) {
	i64 res = 1;
	for(; p; b = b * b % P, p >>= 1) {
		if(p & 1) res = res * b % P;
	}
	return res;
}

int n, m;
int d[N + 5];

namespace paradise {
	const int N = 5e3;

	int ct[N + 5];
	i64 C[N + 5][N + 5];
	void pre() {
		for(int i = 0; i <= N; i++) C[i][0] = 1;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
			}
		}
	}

	int main() {
//		debug("Entering paradise...\n");

		pre();
		for(int i = 1; i <= n; i++) {
			for(int j = d[i]; j >= 2; j--) {
				(ct[j] += C[d[i]][j]) %= P;
			}
		}
		i64 ans = 0;
		for(int i = 2; i <= n - 1; i++) ans ^= ct[i];
		printf("%lld\n", ans);
		return 0;
	}
};

namespace paradox {
	const int N = 1e6;

	i64 fac[N + 5], ifac[N + 5];
	void pre() {
		fac[0] = 1; for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % P;
		ifac[N] = fpow(fac[N], P - 2); for(int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % P;
	}
	i64 C(int n, int m) {
		if(n < 0 || m < 0 || n < m) return 0;
		return fac[n] * ifac[m] % P * ifac[n - m] % P;
	}

	int main() {
//		debug("Entering paradox...\n");

		pre();
		i64 ans = 0;
		for(int i = n - 1; i >= 2; i--) ans ^= C(n - 1, i);
		printf("%lld\n", ans);
		return 0;
	}
};

int main() {
	freopen("mondstadt.in", "r", stdin), freopen("mondstadt.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		d[u]++, d[v]++;
	}

	int ct = 0;
	for(int i = 1; i <= n; i++) ct += (d[i] != 1);

	if(n <= 5000) return paradise::main();
	if(ct == 1) return paradox::main();
	return 0;
}
