#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	int a = 0;
	while(c >= '0' && c <= '9')
	{
		a = a * 10 + c - '0';
		c = getchar();
	}
	return a;
}

const int N = 114514;
int n, k, q;

map <pair <int, int>, int> p;

int son[N][2];
int cf[N];

int dfs(int st, int k)
{
	if(p[make_pair(st, k)])
		return p[make_pair(st, k)];
//	cerr << st << " " << k << "\n";
	return p[make_pair(st, k)] = (cf[st] == 2 ? min(dfs(son[st][0], k), dfs(son[st][1], k)) : max(dfs(son[st][0], k), dfs(son[st][1], k)));
}

int op[N], x[N], y[N];
bitset <14> c[N];

signed main()
{
	freopen("compose.in", "r", stdin);
	freopen("compose.out", "w", stdout);
	n = read();
	k = read();
	q = read();
	for(int i = 1; i <= k; i = i + 1)
	{
		c[i][i] = 1;
		for(int j = 1; j <= n; j = j + 1)
		{
			int tmp;
			tmp = read();
			p[make_pair(i, j)] = tmp;
		}
	}
	int cnt = k;
	bool f = true;
	for(int i = 1; i <= q; i = i + 1)
	{
//		cerr << q << " ";
		op[i] = read();
		if(op[i] == 2)
			f = false;
		x[i] = read();
		y[i] = read();
//		if(op[i] == 3)
//		{
//			cout << dfs(x, y) << "\n";
//			continue;
//		}
//		cf[++ cnt] = op[i];
//		son[cnt][0] = x[i];
//		son[cnt][1] = y[i];
	}
	if(!f)
	{
		for(int i = 1; i <= q; i = i + 1)
		{
			if(op[i] == 3)
			{
				cout << dfs(x[i], y[i]) << "\n";
				continue;
			}
			cf[++ cnt] = op[i];
			son[cnt][0] = x[i];
			son[cnt][1] = y[i];
		}
		return 0;
	}
	for(int i = 1; i <= q; i = i + 1)
	{
		if(op[i] == 3)
		{
			int maxn = 0;
			for(int j = 1; j <= 12; j = j + 1)
				if(c[x[i]][j])
					maxn = max(maxn, p[make_pair(j, y[i])]);
			cout << maxn << "\n";
			continue;
		}
		c[++ cnt] = c[x[i]] | c[y[i]];
	}
	return 0;
}
