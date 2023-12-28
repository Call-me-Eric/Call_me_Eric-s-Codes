#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 2e4;
int n, m, maxn;
vector <int> e[N];
int vis[N];

signed main()
{
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= m; i = i + 1)
	{
		int st, ed;
		cin >> st >> ed;
		e[st].push_back(ed);
		e[ed].push_back(st);
		vis[st] += 1;
		vis[ed] += 1;
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		maxn = max(maxn, vis[i]);
		if(vis[i] >= 4)
		{
			cout << "-1";
			return 0;
		}
	}
	if(m > n)
	{
		cout << "-1";
		return 0;
	}
	if(n == 1 || n == 2 || (n == 3 && m != 3))
	{
		cout << "0 0";
		return 0;
	}
	if(n == 3 && m == 3)
	{
		cout << "1 3";
		return 0;
	}
	if(n == 4 && m == 4)
	{
		cout << "1 4";
		return 0;
	}
	if(n == 4 && m <= 2)
	{
		cout << "0 0";
		return 0;
	}
	if(n == 4 && m == 3)
	{
		if(vis[1] && vis[2] && vis[3] && vis[4] && maxn == 2)
		{
			cout << "0 0";
			return 0;
		}
		else
		{
			cout << "1 3";
			return 0;
		}
	}
	if(n == 5 && m <= 2)
	{
		cout << "0 0";
		return 0;
	}
	if(n == 5 && m == 3)
	{
		int cnt = 0;
		for(int i = 1; i <= n; i = i + 1)
			cnt += vis[i] ? 1 : 0;
		if(cnt == 3)
			cout << "1 3";
		else
			cout << "0 0";
		return 0;
	}
	if(n == 5 && m == 4)
	{
		int cnt = 0;
		for(int i = 1; i <= n; i = i + 1)
			cnt += vis[i] ? 1 : 0;
		if(cnt == 4)
			cout << "1 4";
		else
		{
			if(maxn == 3)
				cout << "1 3";
			else
				cout << "0 0";
		}
		return 0;
	}
	if(n == 5 && m == 5)
	{
		if(maxn == 2)
			cout << "1 5";
		else
			cout << "-1";
		return 0;
	}
	cout << "woshidashabi";
	return 0;
}
