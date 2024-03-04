#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 2e6 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e18;
const double pi = acos(-1);
int n;
int a[N];
int f[N][3]; //0 itself , 1 son , 2 fa
vector<int>e[N];
void dfs(int u, int fa) {
	vector<int>g;
	f[u][0] = a[u];
	for(auto v : e[u]) {
		if(v == fa) continue;
		dfs(v, u);
		f[u][0] += min(f[v][0], min(f[v][1], f[v][2]));
		f[u][2] += min(f[v][0], f[v][1]);
		f[u][1] += f[v][0], g.push_back(f[v][1] - f[v][0]);
	}
	if(!g.size()) f[u][1] = inf;
	else for(int i = 0; i < g.size() - 1; i++) if(g[i] < 0) f[u][1] += g[i];
}
signed main() {
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u, v;
		u = read(), v = read();
		e[u].push_back(v), e[v].push_back(u);
	}
//	memset(f, 127, sizeof(f));
	dfs(1, 0);
	printf("%lld\n", min(f[1][0], f[1][1]));
	return 0;
}
/*
4
1 17 13 4
1 2
1 3
3 4
*/

