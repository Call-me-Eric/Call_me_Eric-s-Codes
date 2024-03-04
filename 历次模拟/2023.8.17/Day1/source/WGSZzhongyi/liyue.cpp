#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, q;
int a[10005];
int flag[20005];
int f[5005][5005], s[5005][5005];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	cin >> n;
	int cnt = sqrt(2 * n) + 1;
	for (int i = 1; i <= cnt; i++) {
		flag[i * i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			f[i][j] = f[i][j - 1];
			if (flag[a[i] + a[j]]) {
				f[i][j]++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			s[j][i] = s[j - 1][i] + f[j][i];
		}
	}
	cin >> q;
	while (q--) {
		int x, y;
		cin >> x >> y;
		cout << s[y - 1][y] - s[x - 1][y] << '\n';
	}
	return 0;
}
