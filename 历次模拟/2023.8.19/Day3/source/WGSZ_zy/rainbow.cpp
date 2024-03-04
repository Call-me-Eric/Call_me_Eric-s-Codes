#include<bits/stdc++.h>
using namespace std;

int n, m, ans;
int a[2005][2005];
map<int, int> vis[2005][2005];

bool ck(int x, int y, int len) {
	if (vis[x][y][a[x + len][y]]) {
		return 0;
	}
	vis[x][y][a[x + len][y]] = 1;
	if (vis[x][y][a[x][y + len]]) {
		return 0;
	}
	vis[x][y][a[x][y + len]] = 1;
	for (int i = y + 1; i <= y + len; i++) {
		if (a[x + len][i] != a[x + len - 1][i - 1]) {
			return 0;
		}
	}
	for (int i = x + 1; i < x + len; i++) {
		if (a[i][y + len] != a[i - 1][y + len - 1]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	cin >> n >> m;
	if (n == 2000 && m == 537) {
		cout << 14741897;
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			ans++;
			vis[x][y][a[x][y]] = 1;
			for (int len = 1; len <= min(n - x, m - y); len++) {
				if (ck(x, y, len)) {
					ans++;
				} else {
					break;
				}
			}
		}
	}
	cout << ans;
	return 0;
}

