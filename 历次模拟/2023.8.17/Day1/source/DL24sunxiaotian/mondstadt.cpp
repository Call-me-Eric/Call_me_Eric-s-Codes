#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e6 + 0721;
const int mod = 1e9 + 7;
int deg[N];
ll inv[N], fac[N];
ll cnt[N];
int n, m;

void init() {
	fac[0] = fac[1] = 1;
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
	}
	for (int i = 2; i <= n; ++i) inv[i] = inv[i - 1] * inv[i] % mod;
}

ll C(int m, int n) {
//	cout << n << " " << m << " " << fac[n] * inv[m] % mod * inv[n - m] % mod << "\n";
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		++deg[x];
		++deg[y];
	}
	
	init();
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 2; j <= deg[i]; ++j) cnt[j] = (cnt[j] + C(j, deg[i])) % mod;
	}
	
	ll ans = 0;
	for (int i = 2; i <= n - 1; ++i) ans ^= cnt[i];
	
	printf("%lld", ans);
	
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
