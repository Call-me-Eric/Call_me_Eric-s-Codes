#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 1) + (xr << 3) + (cr ^ 48), cr = getchar();
	return xr * F;
}

namespace steven24 {

const int N = 0x0d00;
const int mod = 998244353;
ll f[N][N], g[N];
int col[N], b[N];
int head[N], to[N << 1], nxt[N << 1], cnt;
int n, s, k, tmp;

inline void add_edge(int x, int y) {
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}

void discretization() {
	cnt = 0;
	for (int i = 1; i <= n; ++i) if (col[i]) b[++cnt] = col[i];
	sort(b + 1, b + 1 + cnt);
	tmp = unique(b + 1, b + 1 + cnt) - b - 1;
//	cerr << "tmp = " << tmp << "\n";
	s = k - tmp;
	for (int i = 1; i <= n; ++i) if (col[i]) col[i] = lower_bound(b + 1, b + 1 + tmp, col[i]) - b;
}

void dfs(int x, int fa) {
	if (col[x]) f[x][col[x]] = 1;
	else {
		for (int i = 1; i <= tmp; ++i) f[x][i] = 1;
		if (s) f[x][0] = 1;
	}
	
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (y == fa) continue;
		dfs(y, x);
		if (!col[x]) for (int j = 0; j <= tmp; ++j) f[x][j] = f[x][j] * (mod + g[y] - f[y][j]) % mod;
		else f[x][col[x]] = f[x][col[x]] * (mod + g[y] - f[y][col[x]]) % mod;
	}
	for (int i = 1; i <= tmp; ++i) g[x] = (g[x] + f[x][i]) % mod;
	if (f[x][0]) g[x] = (g[x] + f[x][0] * s) % mod;
}

void main() {
	n = read(), k = read();
	for (int i = 1; i <= n; ++i) col[i] = read();
	for (int i = 1; i < n; ++i) {
		int x = read(), y = read();
		add_edge(x, y);
		add_edge(y, x);
	}
	discretization();
	dfs(1, 0);
	printf("%lld\n", g[1]);
}

}

int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	steven24::main();
	return 0;
}
