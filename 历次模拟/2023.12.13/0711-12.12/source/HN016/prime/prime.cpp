#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int t, l, r, cnt, res, lim = 1e5;
int pr[N], Min[N]; bool isp[N];

inline void calc(int cur) {
	int bit = 0, tmp = cur, a[10];
	while (tmp) a[++bit] = tmp % 10, tmp /= 10;
	reverse(a + 1, a + 1 + bit);
	for (int sta = 1; sta < (1 << bit); ++sta) {
		int num = 0;
		for (int i = 1; i <= bit; ++i)
			if (sta >> (i - 1) & 1)
				num = num * 10 + a[i];
		if (isp[num]) return ;
	}
	return ++res, void();
}

int main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	for (int i = 2; i <= lim; ++i) {
		if (!Min[i]) isp[Min[i] = pr[++cnt] = i] = true;
		for (int j = 1; j <= cnt && i * pr[j] <= lim; ++j) {
			if (pr[j] > Min[i]) break;
			Min[i * pr[j]] = pr[j];
		}
	}
	cin >> t;
	while (t--) {
		cin >> l >> r; res = 0;
		for (int i = l; i <= r; ++i) calc(i);
		cout << res << endl;
	}
	return 0;
}
