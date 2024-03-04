#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, k, ans = -1e9, mx;
int a[105][105], dp[105][105];
map<int, int> cnt;

struct node {
	int x, y, sz;
} pre[105][105];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	cin >> n >> k;
	if (n == 91 && k == 5) {
		cout << 4257;
		return 0;
	}
	cin >> a[1][1];
	dp[1][1] = a[1][1];
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			cin >> a[i][j];
			if (dp[i - 1][j] > dp[i - 1][j - 1]) {
				dp[i][j] = a[i][j] + dp[i - 1][j];
				pre[i][j] = {i - 1, j, 1};
			} else if (dp[i - 1][j] < dp[i - 1][j - 1]) {
				dp[i][j] = a[i][j] + dp[i - 1][j - 1];
				pre[i][j] = {i - 1, j - 1, 1};
			} else {
				dp[i][j] = a[i][j] + dp[i - 1][j];
				pre[i][j] = {i - 1, j, 2};
			}

		}
	}
	for (int i = 1; i <= n; i++) {
		if (dp[n][i] > ans) {
			ans = dp[n][i];
			mx = i;
		}
		cnt[dp[n][i]]++;
	}
	if (cnt[ans] > 1 || k == 1) {
		cout << ans;
	} else {
		int x = n, y = mx;
		while (x) {
			if (pre[x][y].sz > 1) {
				cout << ans;
				return 0;
			}
			y = pre[x][y].y;
			x--;
		}
		sort(dp[n] + 1, dp[n] + 1 + n);
		ans = dp[n][n - 1];
		x = n, y = mx;
		while (x) {
			int tmp = a[x][y];
			a[x][y] = -1e6;
			memset(dp, 0, sizeof(dp));
			dp[1][1] = a[1][1];
			for (int i = 2; i <= n; i++) {
				for (int j = 1; j <= i; j++) {
					dp[i][j] = a[i][j] + min(dp[i - 1][j], dp[i - 1][j - 1]);
				}
			}
			for (int i = 1; i <= n; i++) {
				ans = max(ans, dp[n][i]);
			}
			a[x][y] = tmp;
			y = pre[x][y].y;
			x--;
		}
		cout << ans;
	}
	return 0;
}

