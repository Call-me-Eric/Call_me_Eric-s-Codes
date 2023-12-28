#include <bits/stdc++.h>
using namespace std;
namespace QYB {
	typedef long long ll; const ll P = 998244353;
	int n, q; ll a[705][705], t[705][705];
	void exgcd(ll a, ll b, ll &x, ll &y) {
		if (!b) return x = 1, y = 0, void();
		exgcd(b, a % b, y, x); y -= a / b * x;
	} ll inv(ll a) { ll x, y; exgcd(a, P, x, y); return (x % P + P) % P; }
	void solve() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n + 1; j++) {
				t[i][j] = a[i][j];
			}
		} for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (t[j][i]) {
					ll tmp = t[i][i] * inv(t[j][i]) % P;
					for (int k = i; k <= n + 1; k++) {
						(t[i][k] += P - tmp * t[j][k] % P) %= P;
					} swap(t[i], t[j]);
				}
			}
		} for (int i = n; i >= 1; i--) {
			if (!t[i][i]) return printf(t[i][n + 1]? "No\n": "Many\n"), void();
			for (int j = i - 1; j >= 1; j--) {
				ll tmp = t[j][i] * inv(t[i][i]) % P;
				for (int k = 1; k <= n + 1; k++) {
					(t[j][k] += P - tmp * t[i][k] % P) %= P;
				}
			}
		} for (int i = 1; i <= n; i++) {
			printf("%lld%c", t[i][n + 1] * inv(t[i][i]) % P, " \n"[i == n]);
		}
	} int main() {
		freopen("eq.in", "r", stdin);
		freopen("eq.out", "w", stdout);
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n + 1; j++) {
				scanf("%lld", &a[i][j]);
			}
		} solve();
		while (q--) {
			int z; scanf("%d", &z);
			for (int i = 1; i <= n + 1; i++) {
				scanf("%lld", &a[z][i]);
			} solve();
		} return 0;
	}
} int main() { return QYB::main(); }
