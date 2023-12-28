#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e6 + 10;
int n, k;
int get(int n, int k) {
	if (n == k) {
		for (int i = 1; i <= n; ++ i) cout << 1;
		cout << '\n';
		return n;
	}
	int ans = 0, maxw = 0;
	for (int i = 1; i < n; ++ i) {
		if (n % i == 0) {
			int p = n / i;
			int w = k / p;
			if (w * p > ans) ans = w * p, maxw = i;
		}
	}
	if (maxw == 0) {
		for (int i = 1; i <= n; ++ i) cout << 0;
		cout << '\n';
		return 0;
	}
	int p = n / maxw, w = k / p;
	for (int i = 1; i <= n; i += maxw) {
		for (int j = i; j < i + w; ++ j) cout << 1;
		for (int j = i + w; j < i + maxw; ++ j) cout << 0;
	}
	cout << '\n';
	return ans;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	cin >> n >> k;
	get(n, k);
	return 0;
}