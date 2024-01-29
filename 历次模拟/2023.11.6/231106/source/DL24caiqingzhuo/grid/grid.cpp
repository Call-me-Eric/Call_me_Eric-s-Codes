#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 505;
const int mod = 998244353;
int n, q;
int mapp[N][N];

const int dx[5] = {0, 0,  0, 1, -1};
const int dy[5] = {0, 1, -1, 0,  0};

int cx, cy;

int f[N][N];

bool exist(int x, int y)
{
	return x >= 1 && y >= 1 && x <= n && y <= n;
}

int dfs(int x, int y, int t)
{
	if(x == cx && y == cy)
		return f[x][y] = 1;
	if(t > mapp[x][y])
		return 1;
	if(f[x][y] && t <= mapp[x][y])
		return f[x][y];
	f[x][y] = 1;
	for(int i = 1; i <= 4; i = i + 1)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!exist(nx, ny))
			continue;
		f[x][y] += dfs(nx, ny, mapp[x][y] + 1);
		if(f[x][y] >= mod)
			f[x][y] -= mod;
	}
	return f[x][y];
}

signed main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= n; j = j + 1)
			cin >> mapp[i][j];
	cin >> q;
	while(q --)
	{
		memset(f, 0, sizeof(f));
		cin >> cx >> cy;
		int ans = 0;
		for(int i = 1; i <= n; i = i + 1)
			for(int j = 1; j <= n; j = j + 1)
				ans += dfs(i, j, 0);
//		for(int i = 1; i <= n; i = i + 1)
//		{
//			for(int j = 1; j <= n; j = j + 1)
//				cout << f[i][j] << " ";
//			cout << "\n";
//		}
		cout << ans % mod << "\n";
	}
	return 0;
}
