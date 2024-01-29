#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, mod = 998244353;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

int prime[N], top = 0, notprime[N];

inline void init() {
	int n = 1e5; notprime[1] = notprime[0] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!notprime[i]) prime[++top] = i;
		for (int j = 1; j <= top && i * prime[j] <= n; ++j) {
			notprime[i * prime[j]] = 1;
			if (!(i % prime[j])) break;
		}
	}
}

int stk[N], tp = 0;

int vis[N];

inline bool isp(int x) {
	if (!x) return 0;
	if (x == 1) return 0; 
	if (x == 2) return 1;
	for (int i = 2; i * i <= x; ++i)
		if (!(x % i)) return 0;
	return 1;
}

inline bool check(int s)  {
	tp = 0;
	while (s) stk[++tp] = s % 10, s /= 10;
	reverse(stk + 1, stk + tp + 1);
	for (int i = 1; i < (1 << tp); ++i) {
		int r = 0;
		for (int j = 0; j < tp; ++j)
			if ((i >> j) & 1) r = (r * 10) + stk[j + 1];
		if (isp(r)) return 0;
	} return 1;
}

int res[N * 20], cnt = 0;

inline void dfs(int now, int w) {
	if (!now) {
		if (check(w)) res[++cnt] = w;
		return ;
	}
	++vis[0]; vis[40] += vis[4];
	dfs(now - 1, w * 10); --vis[0];
	vis[40] -= vis[4];
	if (!vis[1] && !vis[4] && !vis[6] && vis[8] < 2 && vis[9] < 2) {
		++vis[1]; dfs(now - 1, w * 10 + 1); --vis[1];
	}
	++vis[4]; dfs(now - 1, w * 10 + 4); --vis[4];
	++vis[6]; dfs(now - 1, w * 10 + 6); --vis[6];
	++vis[8]; dfs(now - 1, w * 10 + 8); --vis[8];
	if (!vis[1] && !vis[8] && vis[4] < 2 && !vis[40] && !vis[49]) {
		vis[49] += vis[4]; ++vis[9];
		dfs(now - 1, w * 10 + 9);
		--vis[9]; vis[49] -= vis[4];
	}
}

int main() {
	freopen("prime.in", "r", stdin); freopen("prime.out", "w", stdout);
	dfs(8, 0); sort(res + 1, res + cnt + 1);
	res[++cnt] = 1000000000;
	int T = read();
	while (T--) {
		int l, r; l = read(); r = read();
		int x = upper_bound(res + 1, res + cnt + 1, r) - res - 1;
		x -= upper_bound(res + 1, res + cnt + 1, l - 1) - res - 1;
		printf("%d\n", x % mod);
	}
	return 0;
}
