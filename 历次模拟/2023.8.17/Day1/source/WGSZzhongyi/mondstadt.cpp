#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;

int n, m, ans;
int f[5005][5005];
vector<int> p[5005];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	cin >> n >> m;
	f[0][0] = f[1][0] = f[1][1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i][0] = f[i][i] = 1;
		for (int j = 1; j < i; j++) {
			(f[i][j] = f[i - 1][j] + f[i - 1][j - 1]) %= mod;
		}
	}
	for (int i = 1, x, y; i <= m; i++) {
		cin >> x >> y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	for (int k = 2; k <= n - 1; k++) {
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if ((int)p[i].size() >= k) {
				(cnt += f[p[i].size()][k]) %= mod;
			}
		}
		(ans ^= cnt) %= mod;
	}
	cout << ans;
	return 0;
}
