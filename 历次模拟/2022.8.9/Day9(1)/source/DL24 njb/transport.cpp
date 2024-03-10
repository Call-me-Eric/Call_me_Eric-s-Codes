#include <cstdio>

const int N = 1e5 + 5;

struct Edge {
	int to;
	int nxt;
	int w;
} e[N << 1];

int head[N];
int a[N];
int n, tot, ans;

inline void add(int u, int v, int w) {
	e[++tot].to = v;
	e[tot].w = w;
	e[tot].nxt = head[u];
	head[u] = tot;
}

inline void dfs(int u, int pre, int sum) {
	++ans;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to, w = e[i].w;
		if (v == pre) continue;
		else if (sum + w < 0) continue;
		else dfs(v, u, sum + w);
	}
}

int main() {
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1, u, v, w; i < n; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, a[u] - w), add(v, u, a[v] - w);
	}
	for (int i = 1; i <= n; ++i) dfs(i, -1, 0);
	printf("%d\n", ans - n);
	fclose(stdin), fclose(stdout);
	return 0;
}

