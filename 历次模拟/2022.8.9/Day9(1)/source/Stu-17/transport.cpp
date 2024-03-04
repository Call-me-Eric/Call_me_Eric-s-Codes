#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>

using namespace std;

inline int read(void)
{
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

int n;
long long ans = 0;
int a[100005];

struct edge
{
	int v, d;
	edge(int v = 0, int d = 0) :
		v(v), d(d) {}
};
vector <edge> G[100005];

bool v[100005];
void dfs(int x, int res)
{
	v[x] = true, res += a[x], ++ans;
	for (int i = 0; i < G[x].size(); ++i)
	{
		int y = G[x][i].v, w = G[x][i].d;
		if (!v[y] && res >= w) dfs(y, res - w);
	}
}

int main(void)
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i)
	{
		int u = read(), v = read(), w = read();
		G[u].push_back(edge(v, w));
		G[v].push_back(edge(u, w));
	}
	for (int i = 1; i <= n; ++i)
	{
		memset(v, 0, sizeof(v));
		dfs(i, 0);
	}
	printf("%lld\n", ans - n);
	return 0;
}
