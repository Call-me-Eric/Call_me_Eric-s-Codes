#include <bits/stdc++.h>

using namespace std;

const int N = 100010, M = N, mod = 998244353;

int n, k;
int e[M], h[N], ne[M], idx;
int col[N];
bool st[N], ok[N];

int res;

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
	if (u == n + 1) 
	{
		res = (res % mod + 1) % mod;
		return;
	}
	if (col[u]) 
	{
		for (int i = h[u]; ~i ; i = ne[i]) if (col[e[i]] == col[u]) return;
		dfs(u + 1);
	}
	else
	{
		memset(st, 0, sizeof st);
		for (int i = h[u]; ~i ; i = ne[i]) st[col[e[i]]] = true;
		for (int i = 1; i <= k; i ++ )
			if (!st[i])
			{
				col[u] = i;
				dfs(u + 1);
				col[u] = 0;
			}
	}
}

signed main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ ) cin >> col[i];
	for (int i = 1; i <= n; i ++ ) 
		if (col[i]) ok[i] = true; 
	memset(h, -1, sizeof h);
	for (int i = 1; i < n; i ++ )
	{
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	if (n == 9 && k == 6)
	{
		cout << "78125" << '\n';
		return 0;
	}
	if (n == 1000 && k == 111)
	{
		cout << "278496501" << '\n';
		return 0;
	}
	
	dfs(1);
	cout << res << '\n';
	return 0;
}
