#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000 + 5;

int N , M , K;

struct Seg {
	int l , r;
	int operator <(const Seg &rhs) const {
		return r == rhs.r ? l < rhs.l : r < rhs.r;
	}
} a[MAXN];

int L[MAXN] , f[MAXN][MAXN];

int main() {
  freopen("stamps.in", "r", stdin);
  freopen("stamps.out", "w", stdout);
	cin.tie(nullptr)->sync_with_stdio(0);

	int T , CASE = 0;
	// cin >> T;
	T = 1;

	while (T--) {
		cin >> N >> M >> K;
		assert(1 <= K && K <= M);
		assert(1 <= N && N <= 2000);
		assert(1 <= M && M <= 2000);
		for (int i = 0 ; i <= N ; i++) {
			L[i] = N + 1;
		}
		for (int i = 1 ; i <= M ; i++) {
			cin >> a[i].l >> a[i].r;
			assert(1 <= a[i].l && a[i].l <= a[i].r);
			assert(a[i].l <= a[i].r && a[i].r <= N);
			for (int j = a[i].l ; j <= a[i].r ; j++) {
				L[j] = min(L[j] , a[i].l);
			}
		}
		for (int i = 0 ; i <= N ; i++) {
			for (int j = 0 ; j <= K ; j++) {
				f[i][j] = 0;
			}
		}
		int ans = 0;
		for (int i = 1 ; i <= N ; i++) {
			for (int j = 0 ; j <= K ; j++) {
				f[i][j] = max(f[i][j] , f[i - 1][j]);
				if (j > 0) {
					f[i][j] = max(f[i][j] , f[i - 1][j]);
					if (L[i] != N + 1) {
						f[i][j] = max(f[i][j] , f[L[i] - 1][j - 1] + i - L[i] + 1);
					}
				}
				ans = max(ans , f[i][j]);

			}
		}
		cout << ans << '\n';
		// cout << "Case #" << ++CASE << ": " << ans << '\n';
	}
	return 0;
}
