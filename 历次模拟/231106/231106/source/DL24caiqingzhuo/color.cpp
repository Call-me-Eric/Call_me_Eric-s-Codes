#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1114;
const int mod = 998244353;
int f[N][N];

int n, k;
int col[N];
vector <int> e[N];

void dfs(int st, int fa)
{
	if(col[st] == 0)
		for(int i = 1; i <= k; i = i + 1)
			f[st][i] = 1;
	else
		f[st][col[st]] = 1;
	for(int i = 0; i < e[st].size(); i = i + 1)
	{
		int ed = e[st][i];
		if(ed == fa)
			continue;
		dfs(ed, st);
		if(!col[st])
			for(int j = 1; j <= k; j = j + 1)
				(f[st][j] *= (f[ed][0] - f[ed][j])) %= mod;
		else
			(f[st][col[st]] *= (f[ed][0] - f[ed][col[st]])) %= mod;
	}
	for(int i = 1; i <= k; i = i + 1)
		(f[st][0] += f[st][i]) %= mod;
}

signed main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i = i + 1)
		cin >> col[i];
	for(int i = 1; i <= n - 1; i = i + 1)
	{
		int st, ed;
		cin >> st >> ed;
		e[st].push_back(ed);
		e[ed].push_back(st);
	}
	dfs(1, 0);
	cout << (f[1][0] % mod + mod) % mod;
//	for(int i = 1; i <= n; i = i + 1)
//	{
//		for(int j = 0; j <= k; j = j + 1)
//			cout << f[i][j] << " ";
//		cout << "\n";
//	}
	return 0;
}
