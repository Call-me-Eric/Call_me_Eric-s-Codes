# include <cstdio>
# include <cctype>
# include <algorithm>

# define int long long

using std::min;

constexpr int MAXN = 1e6 + 5;

class IO {
	static constexpr int MAXS = 1 << 20;
	
	char buf[MAXS], *p1 = buf, *p2 = buf;
	
	# define GetC() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXS, stdin), p1 == p2) ? EOF : *p1 ++)
	
 public:
	template <typename T> inline void read(T& x) {
		x = 0; char ch = GetC();
		for (; !isdigit(ch); ch = GetC());
		for (; isdigit(ch); ch = GetC()) x = x * 10 + ch - '0';
	}
	
	template <typename T, typename ...Args> inline void read(T& x, Args& ...rest) {
		read(x), read(rest...);
	}
} io;

int n;

int val[MAXN << 1];

int head[MAXN << 1], numE;

struct Edge {
	int nxt, to;
	
	Edge(int N = 0, int T = 0) {
		nxt = N, to = T;
	}
} edge[MAXN << 1];

void addE2(int x, int y) {
	edge[++numE] = Edge(head[x], y); head[x] = numE;
	edge[++numE] = Edge(head[y], x); head[y] = numE;
}

int f[MAXN << 1][3];

void dfs(int u, int father) {
	f[u][0] = val[u];
	bool flg = true; int mn = 1e9;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if (k == father) continue;
		dfs(k, u);
		f[u][0] += min({ f[k][0], f[k][1], f[k][2] });
		if (f[k][0] <= f[k][1]) flg = false;
		mn = min(mn, f[k][0] - f[k][1]), f[u][1] += min(f[k][0], f[k][1]);
		f[u][2] += min(f[k][0], f[k][1]);
	}
	if (flg) f[u][1] += mn;
}

signed main() {
	
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	
	io.read(n);
	for (int i = 1; i <= n; ++i) io.read(val[i]);
	for (int i = 1; i < n; ++i) {
		int x, y; io.read(x, y); addE2(x, y);
	}
	dfs(1, 0);
	printf("%lld\n", min(f[1][0], f[1][1]));
	
	return 0;
}
