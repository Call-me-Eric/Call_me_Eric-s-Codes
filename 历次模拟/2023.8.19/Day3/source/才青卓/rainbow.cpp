#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[2114][2114];
bool tong[10100];

void csh()
{
	for(int i = 1; i <= n * m; i = i + 1)
		tong[i] = false;
}

bool checkn(int x, int y, int k)
{
	csh();
	for(int i = 0; i <= k; i = i + 1)
	{
		for(int j = 0; j <= k; j = j + 1)
		{
			if(i == 0 || j == 0)
			{
				if(tong[a[x + i][y + j]] == 1)
					return false;
				else
					tong[a[x + i][y + j]] = 1;
			}
			else
				if(a[x + i][y + j] != a[x + i - 1][y + j - 1])
					return false;
		}
	}
	return true;
}

int main()
{
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= m; j = j + 1)
			cin >> a[i][j];
	int ans = 0;
	for(int i = 1; i <= n; i = i + 1)
	{
		for(int j = 1; j <= m; j = j + 1)
		{
			for(int k = 1; k <= min(n - i, m - j); k = k + 1)
			{
				ans += checkn(i, j, k);
			}
		}
	}
	cout << ans + n * m;
	return 0;
}
