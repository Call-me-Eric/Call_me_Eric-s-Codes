#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

const int N = 81, bas = 131, P = 998244353;
int n, m, q, k, len, res, a[N], b[N], curb[N], cura[N];
gp_hash_table <unsigned, int> calc;

inline unsigned ha(unsigned h = 0) { for (int i = 1; i <= len; ++i) h = h * bas + cura[i]; return h; }
inline unsigned hb(unsigned h = 0) { for (int i = 1; i <= len; ++i) h = h * bas + curb[i]; return h; }

inline void dfsa(int step) {
	bool ok = true;
	for (int i = 1; i <= len; ++i) ok &= (cura[i] >= cura[i + 1]);
	if (!ok) return ;
	if (step == k / 2) return ++calc[ha()], void();
	for (int i = 1; i <= len; ++i) {
		++cura[i], dfsa(step + 1), --cura[i];
		--cura[i], dfsa(step + 1), ++cura[i];
	}
	return ;
}

inline void dfsb(int step) {
	bool ok = true;
	for (int i = 1; i <= len; ++i) ok &= (curb[i] >= curb[i + 1]);
	if (!ok) return ;
	if (step == k - k / 2) return (res += calc[hb()]) %= P, void();
	for (int i = 1; i <= len; ++i) {
		++curb[i], dfsb(step + 1), --curb[i];
		--curb[i], dfsb(step + 1), ++curb[i];
	}
	return ;
}

inline void solve() {
	cin >> k; len = max(n, m) + k, res = 0, calc.clear();
	dfsa(0), dfsb(0); return cout << res << endl, void();
}

int main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i], cura[i] = a[i];
	cin >> m; for (int i = 1; i <= m; ++i) cin >> b[i], curb[i] = b[i];
	cin >> q; while (q--) solve();
	return 0;
}
