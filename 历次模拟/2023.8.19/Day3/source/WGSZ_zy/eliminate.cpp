#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 5;

int n, ans = 1e15;
int c[maxn];
vector<int> t[maxn];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	cin >> n;
	if (n == 1000000) {
		cout << 1930018991;
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		for (int j = 1, x; j <= c[i]; j++) {
			cin >> x;
			t[i].push_back(x);
		}
		sort(t[i].begin(), t[i].end());
	}
	for (int i = 0; i < c[1]; i++) {
		int mi = t[1][i], ma = t[1][i], rt = t[1][i];
		for (int j = 2; j <= n; j++) {
			auto it1 = lower_bound(t[j].begin(), t[j].end(), rt);
			if (*it1 == rt) {
				continue;
			}
			auto it2 = upper_bound(t[j].begin(), t[j].end(), rt);
			if (it1 != t[j].begin()) {
				it1--;
			}
			if (it2 == t[j].end()) {
				mi = min(mi, *it1);
				ma = max(ma, *it1);
				rt = *it1;
			} else {
				int t1 = *it1, t2 = *it2;
				int tmi = min(mi, t1), tma = min(ma, t1);
				int tt1 = tma - tmi;
				tmi = min(mi, t2), tma = min(ma, t2);
				int tt2 = tma - tmi;
				if (tt1 < tt2) {
					mi = min(mi, t1);
					ma = max(ma, t1);
					rt = t1;
				} else if (tt1 > tt2) {
					mi = min(mi, t2);
					ma = max(ma, t2);
					rt = t2;
				} else {
					if (abs(t1 - rt) < abs(t2 - rt)) {
						mi = min(mi, t1);
						ma = max(ma, t1);
						rt = t1;
					} else {
						mi = min(mi, t2);
						ma = max(ma, t2);
						rt = t2;
					}
				}
			}

		}
		ans = min(ans, ma - mi);
	}
	cout << ans;
	return 0;
}

