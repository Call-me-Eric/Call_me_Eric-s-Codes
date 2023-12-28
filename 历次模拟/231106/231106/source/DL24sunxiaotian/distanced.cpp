#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9')
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

namespace steven24 {

const int N = 25;
bool vis[N];
int fa[N];
int tmp[N];
ll ans[N];
int n, T;

struct node {
	int loc, val;
	friend bool operator<(node x, node y) {
		return x.loc < y.loc;
	}
} a[N];

inline int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	fa[fx] = fy;
}

void solve() {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	ll sum = 0;
	for (int i = 1; i <= n; ++i) if (vis[i]) sum += a[i].val;
	for (int i = 1; i <= n; ++i) if (vis[i]) tmp[++cnt] = a[i].loc;
	
	for (int i = 2; i <= cnt; ++i) if (tmp[i] - tmp[i - 1] <= T) merge(i, i - 1);
	int s = 0;
	for (int i = 1; i <= cnt; ++i) if (fa[i] == i) ++s;
	ans[s] = max(ans[s], sum);
} 

void dfs(int x) {
	if (x == n + 1) {
		solve();
		return;
	}
	
	vis[x] = 1;
	dfs(x + 1);
	vis[x] = 0;
	dfs(x + 1);
}

void main() {
	n = read(), T = read();
	for (int i = 1; i <= n; ++i) a[i].loc = read();
	for (int i = 1; i <= n; ++i) a[i].val = read();
	sort(a + 1, a + 1 + n);
	dfs(1);
	for (int i = 1; i <= n; ++i) ans[i] = max(ans[i], ans[i - 1]);
	for (int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	printf("\n");
} 

}

int main() {
	freopen("distanced.in", "r", stdin);
	freopen("distanced.out", "w", stdout);
	steven24::main();
	return 0;
}
