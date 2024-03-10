#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-2;
const int N = 1e6 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 1e9 + 7;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, m;
int rd[N];
int qpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int fac[N], ifac[N];
void init() {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
int C(int n, int m) {
	if(n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
signed main() {
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= m; i++)	{
		int u, v;
		u = read(), v = read();
		rd[u]++, rd[v]++;
	}
	init();
	int ans = 0;
	for(int k = 2; k <= n - 1; k++) {
		int res = 0;
		for(int i = 1; i <= n; i++) res += C(rd[i], k), res %= mod;
//		cout << res << endl;
		ans ^= res;
		ans %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}

