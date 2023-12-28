#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

int n, k;

vector<int> fac;

const double PI = acos(-1);

inline double abs_(double x) {
	return x < 0 ? -x : x;
}

inline bool check(int S) {
	if (__builtin_popcount(S) > k) return 0;
	double x = 0, y = 0;
	for (int i = 0; i < n; ++i) {
		if (!((S >> i) & 1)) continue;
		x += cos(2.0 * PI * i / n);
		y += sin(2.0 * PI * i / n);
	} return abs_(x) < 1e-6 && abs_(y) < 1e-6;
}

bool ans[N];

int main() {
	freopen("ur.in", "r", stdin); freopen("ur.out", "w", stdout);
	n = read(); k = read();
	if (n == k) {
		for (int i = 1; i <= n; ++i) putchar('1');
		return 0;
	}
	if (k <= 1) {
		for (int i = 1; i <= n; ++i) putchar('0');
		return 0;
	} int t = n;
	for (int i = 2; i * i <= t; ++i) {
		if (!(t % i)) {
			fac.push_back(i);
			if (t / i != i) fac.push_back(t / i);
		}
	} int m = fac.size();
	if (!m) {
		for (int i = 1; i <= n; ++i) putchar('0');
		return 0;
	}
	if (n <= 20) {
		int res = 0;
		for (int i = 0; i < (1 << n); ++i)
			if (check(i) && __builtin_popcount(i) > __builtin_popcount(res)) res = i;
		for (int i = 0; i < n; ++i) putchar('0' + ((res >> i) & 1));
		return 0;
	} sort(fac.begin(), fac.end());
	int cnt = 0;
	for (int i : fac) {
		for (int j = 0; j < n / i; ++j) {
			if (cnt + n / i > k) break;
			bool fl = 1;
			for (int k = j; k < n; k += n / i) {
				if (ans[k]) {
					fl = 0;
					continue;
				}
			}
			if (fl) {
				cnt += n / i;
				for (int k = j; k < n; k += n / i) ans[k] = 1;
			}
		}
	}
	for (int i = 0; i < n; ++i) putchar(ans[i] ^ 48);
	return 0;
}