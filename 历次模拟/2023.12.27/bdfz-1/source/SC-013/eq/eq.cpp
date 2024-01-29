#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 705, mod = 998244353;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

inline int power(int a, int b) {
	int t = 1, y = a, k = b;
	while (k) {
		if (k & 1) t = (1ll * t * y) % mod;
		y = 1ll * y * y % mod; k >>= 1;
	} return t;
}

int a, b, n, q;

inline void calc() {
	if (!a) puts(b ? "No" : "Many");
	else printf("%lld\n", 1ll * b * power(a, mod - 2) % mod);

}

int main() {
	freopen("eq.in", "r", stdin); freopen("eq.out", "w", stdout);
	n = read(); q = read();
	a = read(); b = read();
	calc();
	while (q--) {
		a = read(); b = read();
		calc();
	} return 0;
}