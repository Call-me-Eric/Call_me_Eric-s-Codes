#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>

using namespace std;

inline int read(void)
{
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

void print(int x)
{
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, tag;
bool v[2][1000005];
vector <int> G[2][1000005];

void dfs(int x)
{
	v[tag][x] = true;
	for (int i = 0; i < G[tag][x].size(); ++i)
	{
		int y = G[tag][x][i];
		if (!v[tag][y]) dfs(y);
	}
}

inline bool check(void)
{
	for (int i = 1; i <= n; ++i)
		if (!(v[0][i] || v[1][i])) return false;
	return true;
}

int tot = 0, ans[1000005];

int main(void)
{
	freopen("goood.in", "r", stdin);
	freopen("goood.out", "w", stdout);
	n = read(), m = read();
	while (m--)
	{
		int u = read(), v = read();
		G[0][u].push_back(v);
		G[1][v].push_back(u);
	}
	for (int i = 1; i <= n; ++i)
	{
		memset(v, 0, sizeof(v));
		tag = 0;
		dfs(i);
		tag = 1;
		dfs(i);
		if (check()) ans[++tot] = i;
	}
	print(tot); putchar('\n');
	for (int i = 1; i <= tot; ++i)
	{
		print(ans[i]);
		putchar(' ');
	}
	putchar('\n');
	return 0;
}
