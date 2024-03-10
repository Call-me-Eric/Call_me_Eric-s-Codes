#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e6 + 5;

int rd() {
	int res = 0;
	char x = getchar();
	while (!isdigit(x)) {
		x = getchar();
	}
	res += x ^ 48;
	while (isdigit(x = getchar())) {
		res = (res << 3) + (res << 1) + (x ^ 48);
	}
	return res;
}

int min(int x, int y) {
	return x > y ? y : x;
}

int n;
int a[maxn], dp[maxn][2];
vector<int> p[maxn];

void dfs(int u, int fa) {
	int f1 = 0, f2 = 1e18, f3 = 0;
	for (auto v : p[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		dp[u][1] += min(dp[v][1], dp[v][0]);
		if (p[v].size() == 1) {
			dp[u][0] += dp[v][1];
		} else {
			dp[u][0] += min(dp[v][1], dp[v][0]);
		}
		if (dp[v][1] <= dp[v][0]) {
			f1 = 1;
		}
		if (dp[v][1] < f2) {
			f2 = dp[v][1];
			f3 = v;
		}
	}
	if (!f1 && p[u].size() > 1) {
		dp[u][0] -= dp[f3][0];
		dp[u][0] += f2;
	}
	dp[u][1] += a[u];
}

signed main() {
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	n = rd();
	for (int i = 1; i <= n; i++) {
		a[i] = rd();
	}
	for (int i = 1, u, v; i < n; i++) {
		u = rd(), v = rd();
		p[u].push_back(v);
		p[v].push_back(u);
	}
	dfs(1, 0);
	cout << min(dp[1][0], dp[1][1]);
	return 0;
}

