# include <cstdio>
# include <vector>
# include <queue>
# include <utility>
# include <cstring>

# define int long long

typedef std::pair<int, int> Pii;

constexpr int MAXN = 500 + 5, MAXM = 1e3 + 5;

int n, num;

int a[MAXN << 1], b[MAXN << 1];

int head[MAXN << 1], numE;

struct Edge {
	int nxt, to, val;
	
	Edge() {}
	Edge(int N, int T, int V) {
		nxt = N, to = T, val = V;
	}
} edge[MAXM << 1];

void addE2(int x, int y, int val) {
	edge[++numE] = Edge(head[x], y, val), head[x] = numE;
	edge[++numE] = Edge(head[y], x, val), head[y] = numE;
}

int f[9][MAXN][MAXN];

int dis[MAXN << 1];

int g[MAXN][1 << 8];

bool vis[MAXN << 1];

void dij(int s) {
	std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hp;
	memset(dis, 0x3f, sizeof dis);
	memset(vis, false, sizeof vis); 
	dis[s] = 0, hp.emplace(0, s);
	
	while (!hp.empty()) {
		int u = hp.top().second; hp.pop();
		if (!vis[u]) {
			vis[u] = true;
			for (int i = head[u]; i; i = edge[i].nxt) {
				int k = edge[i].to;
				if (dis[k] > dis[u] + edge[i].val)
					dis[k] = dis[u] + edge[i].val, hp.emplace(dis[k], k);
			}
		}
	}
}

signed main() {
	
	freopen("subway.in", "r", stdin);
	freopen("subway.out", "w", stdout);
	
	scanf("%lld %lld", &n, &num);
	memset(f, 0x3f, sizeof f);
	for (int k = 1; k <= num; ++k) for (int i = 1; i <= n; ++i) f[k][i][i] = 0;
	for (int i = 1; i <= num; ++i) {
		for (int j = 1; j <= n; ++j) scanf("%lld", &a[j]);
		for (int j = 1; j <= n; ++j) scanf("%lld", &b[j]);
		int m; scanf("%lld", &m);
		memset(head, 0, sizeof head), numE = 0;
		for (int j = 1; j <= m; ++j) {
			int x, y, val;
			scanf("%lld %lld %lld", &x, &y, &val);
			addE2(x, y, val);
		}
		for (int s = 1; s <= n; ++s) {
			dij(s);
			for (int t = 1; t <= n; ++t) f[i][s][t] = dis[t] + a[s] + b[t];
		}
	}
	
	memset(g, 0x3f, sizeof g);
	g[1][0] = 0; int ans = 1e18;
	for (int i = 2; i <= n; ++i) {
		for (int s = 1; s < 1 << num; ++s) {
			for (int k = 0; k < num; ++k) if (1 << k & s) {
				for (int j = 1; j <= n; ++j) {
					g[i][s] = std::min(g[i][s], g[j][s ^ 1 << k] + f[k + 1][j][i]);
				}
			}
			ans = std::min(ans, g[n][s]);
		}
	}
	printf("%lld\n", ans);
	
	return 0;
}
