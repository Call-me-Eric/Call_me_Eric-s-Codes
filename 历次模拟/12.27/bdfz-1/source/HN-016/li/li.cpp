#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
int n, m, len, q[N]; vector <int> g[N];
bool vis[N]; int chain, circle;

template <typename T> inline void read(T &x) {
	x = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
}

template <typename T, typename ...Args>
inline void read(T &x, Args &...args) { read(x), read(args...); }

inline void dfs(int cur) {
	if (vis[cur]) return ;
	vis[cur] = true, q[++len] = cur;
	for (auto to: g[cur]) dfs(to);
	return ;
}

signed main() {
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	read(n, m);
	for (int i = 1, u, v; i <= m; ++i)
		read(u, v), g[u].push_back(v), g[v].push_back(u);
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue; dfs(i);
		if (len == 1) { q[len--] = 0; continue; }
		int cnt1 = 0, cnt2 = 0, cnt3 = 0, other = 0;
		for (int i = 1; i <= len; q[i++] = 0) {
			int deg = g[q[i]].size();
			if (deg == 1) ++cnt1;
			else if (deg == 2) ++cnt2;
			else if (deg == 3) ++cnt3;
			else ++other;
		}
		if (other) return !puts("-1");
		else if (len == 4 && cnt1 == 3 && cnt3 == 1) circle += 3;
		else if (cnt1 == 2 && cnt2 == len - 2) chain += len * (len - 1) / 2;
		else if (cnt2 == len) circle += len;
		else return !puts("-1");
		len = 0;
	}
	if (!circle) return !printf("0 %lld\n", chain + n);
	return !printf("1 %lld\n", circle);
}
