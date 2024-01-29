#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int inv2 = 499122177;

void SUB(int &x, int y) {
	x -= y;
	if (x < 0) x += mod;
}

void ADD(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

long long pw[100010];
int f[100010];

int Calc(int n) {
	if (n & 1) return pw[n + 1 >> 1] * (n + 1ll) % mod;
	return (pw[n >> 1] * (n + 2ll >> 1) + pw[n + 2 >> 1] * (n + 1ll >> 1)) % mod;
}

int main () {
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	int n, k; cin >> n >> k;
	pw[0] = 1; for (int i = 1; i <= 100005; i++) pw[i] = pw[i - 1] * k % mod;
	for (int i = 1; i <= n; i++) {
		f[i] = Calc(i);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		SUB(f[i], pw[i + 1 >> 1]);
		ADD(ans, 1ll * f[i] * (n / i) % mod);
		for (int j = i + i; j <= n; j += i) {
			SUB(f[j], 1ll * f[i] * (j / i) % mod);
		}
	}
	cout << ans << endl;
	return 0;
}