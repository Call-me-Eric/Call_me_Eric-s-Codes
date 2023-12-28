#include <bits/stdc++.h>
using namespace std;
int main() {
	freopen("ur.in", "r", stdin), freopen("ur.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	if (k == n) {
		while (n--) {
			cout << 1;
		}
		return 0;
	}
	if (k <= 1) {
		while (n--) {
			cout << 0;
		}
		return 0;
	}
	using point = complex<double>;
	vector<point> a(n);
	constexpr double pi = acos(-1), eps = 1e-8;
	point now = 1, w(cos(pi * 2 / n), sin(pi * 2 / n));
	for (int i = 0; i < n; i++, now *= w) {
		a[i] = now;
	}
	int mx = 0, ans = 0;
	for (int S = 0; S < (1 << n); S++) {
		int cnt = __builtin_popcount(S);
		if (cnt > k) {
			continue;
		}
		point sum = 0;
		for (int j = 0; j < n; j++) {
			if (S >> j & 1) {
				sum += a[j];
			}
		}
		if (fabs(sum.real()) < eps && fabs(sum.imag()) < eps) {
			if (cnt > mx) {
				mx = cnt;
				ans = S;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << (ans >> i & 1);
	}
	return 0;
}
