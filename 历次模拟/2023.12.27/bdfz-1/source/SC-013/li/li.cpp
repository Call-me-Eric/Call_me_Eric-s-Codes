#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

struct edge {
	int head, to, nxt;
} ed[N << 1];

int en = 0;

inline void addedge(int from, int to) {
	ed[++en].to = to; ed[en].nxt = ed[from].head; ed[from].head = en;
}

int n, m, d[N], c1 = 0, c2 = 0;
long long res = 0, cir = 0;
bool fl = 0;
bool vis[N];

inline void dfs(int now) {
	vis[now] = 1; ++c1; c2 += d[now];
	for (int i = ed[now].head; i; i = ed[i].nxt) {
		int v = ed[i].to;
		if (vis[v]) continue;
		dfs(v);
	}
}

int main() {
	freopen("li.in", "r", stdin); freopen("li.out", "w", stdout);
	n = read(); m = read(); int mx = 0;
	if (m > n) { puts("-1"); return 0; }
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
		++d[u]; ++d[v];
		if (d[u] > 3 || d[v] > 3) {
			puts("-1"); return 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 3) {
			int cnt = 0;
			for (int j = ed[i].head; j; j = ed[j].nxt) {
				int v = ed[j].to;
				vis[v] = 1;
				cnt += d[v];
			} vis[i] = 1;
			cir += 3; fl = 1;
			if (cnt > 3) {
				puts("-1");
				return 0;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		c1 = 0; c2 = 0;
		dfs(i);
		if (c1 * 2 == c2) {
			fl = 1; cir += c1;
		} else {
			res += 1ll * c1 * (c1 + 1) / 2;
		}
	}
	if (fl) printf("1 %lld\n", cir);
	else printf("0 %lld\n", res);
	return 0;
}