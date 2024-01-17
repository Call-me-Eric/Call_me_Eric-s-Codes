#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
int n, k, res[N], vis[N];
vector <int> pri;

inline void Fact() {
	int tmp = n;
	for (int i = 2;i * i <= tmp;i++) {
		if (tmp % i == 0) {
			pri.push_back(i);
			while (tmp % i == 0) tmp /= i;
		}
	}
	if (tmp > 1) pri.push_back(tmp);
	//for (int x : pri) cout << x << " ";
}

inline void Solve() {
	int ansv = -1, ansx = 0, ansy = 0, ansi = 0, ansj = 0;
	for (int x : pri) {
		for (int y : pri) {
			for (int i = 0;i * x <= k;i++) {
				int j = min((k - i * x) / y, n / y - ((i + y - 1) / y * x));
				if (j < 0) break;
				if (i * x + j * y > ansv) {
					ansv = i * x + j * y;
					ansx = x; ansy = y;
					ansi = i; ansj = j;
				}
			}
		}
	}
	//cout << ansx << " " << ansy << " " << ansi << " " << ansj << endl;
	int s = 0;
	for (int k = 0;k < ansi;k++) {
		for (int y = 0;y < ansx;y++) {
			res[(s + 1ll * y * (n / ansx)) % n] = 1;
			vis[(s + 1ll * y * (n / ansx)) % (n / ansy)] = 1;
		}
		s = (s + (n / ansy)) % n;
	}
	int cnt = ansj;
	for (int s = 0;s < n / ansy && cnt;s++) {
		if (!vis[s]) {
			for (int k = 0;k < ansy;k++) res[(s + 1ll * (n / ansy) * k) % n] = 1;
			cnt--;
		}
	}
	for (int i = 0;i < n;i++) cout << res[i];
	cout << endl;
}

int main() {
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	cin >> n >> k;
	if (k <= 1) {
		for (int i = 1;i <= n;i++) cout << 0;
		cout << endl;
		return 0;
	}
	if (k == n) {
		for (int i = 1;i <= n;i++) cout << 1;
		cout << endl;
		return 0;
	}
	Fact();
	Solve();
	return 0;
}
