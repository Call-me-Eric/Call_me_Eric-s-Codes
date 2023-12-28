#include <bits/stdc++.h>
using namespace std;
constexpr int P = 998244353;
int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1LL * res * a % P;
		}
		a = 1LL * a * a % P;
		b /= 2;
	}
	return res;
}
using LL = int64_t;
LL a[701][701], b[701][701];
int main() {
	freopen("eq.in", "r", stdin), freopen("eq.out", "w", stdout);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			cin >> a[i][j];
		}
	}
	auto solve = [&]() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				b[i][j] = a[i][j];
			}
		}
		for (int i = 0; i < n; i++) {
			int mx = 0, pos = 0;
			for (int j = i; j < n; j++) {
				a[j][i] = (a[j][i] % P + P) % P;
				if (a[j][i] >= mx) {
					mx = a[j][i];
					pos = j;
				}
			}
			swap(a[i], a[pos]);
			for (int j = 0; j < n; j++) {
				if (j == i) {
					continue;
				}
				LL d = 1LL * a[j][i] * qpow(a[i][i], P - 2) % P;
				LL *ai = &a[i][0], *ed = ai + n + 1, *aj = &a[j][0], k = 0;
				while (k + 3 <= n) {
					((*aj) -= (*ai) * d) %= P, ai++, aj++, k++;
					((*aj) -= (*ai) * d) %= P, ai++, aj++, k++;
					((*aj) -= (*ai) * d) %= P, ai++, aj++, k++;
					((*aj) -= (*ai) * d) %= P, ai++, aj++, k++;
				}
				while (k <= n) {
					((*aj) -= (*ai) * d) %= P, ai++, aj++, k++;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				a[i][j] = (a[i][j] % P + P) % P;
			}
		}
		bool no = 0, many = 0;
		for (int i = 0; i < n; i++) {
			if (a[i][i] == 0) {
				if (a[i][n] == 0) {
					many = 1;
				} else {
					no = 1;
				}
			}
		}
		if (no) {
			cout << "No" << "\n";
		} else if (many) {
			cout << "Many" << "\n";
		} else {
			for (int i = 0; i < n; i++) {
				cout << 1LL * a[i][n] * qpow(a[i][i], P - 2) % P << " \n"[i + 1 == n];
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				a[i][j] = b[i][j];
			}
		}
	};
	solve();
	while (q--) {
		int row;
		cin >> row;
		row--;
		for (int j = 0; j < n + 1; j++) {
			cin >> a[row][j];
		}
		solve();
	}
	return 0;
}
