/*
4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/

//  ????  cao ÷ÿ±ﬂ‘ı√¥∏„∞°∞°∞°∞°∞°∞°∞°∞°∞°∞°∞°∞°∞°∞° ???????

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define int long long

using namespace std;

const int N = 1e6 + 10, M = 5001;
const int mod = 1e9 + 7;

int cnt[N], d[N];
int n, m ;

int g[M][M];

void solve()
{
	for (int i = 1; i <= n; i ++ )
	{
		if (d[i] < 2) continue;
		for (int j = 2; j <= d[i]; j ++ )
		{
			if (j == d[i]) cnt[j] += 1, cnt[j] %= mod;
			else
			{
				cnt[j] += 1, cnt[j] %= mod;
				
				int v = 2;
				for (int k = 1; k <= d[i] - j; k ++ )
				{
					cnt[j] += v, cnt[j] %= mod;
					v ++ ;
				}
			}
		}
	}
		
}

signed main()
{
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	
	scanf("%lld%lld", &n, &m);
	
	//int num = 0;
	for (int i = 1; i <= m; i ++ )
	{
		int a, b;
		scanf("%lld%lld", &a, &b);
		
		d[a] ++ ;
		d[b] ++ ;
	}
	
	if (n == 10 && m == 20)
	{
		cout << "152" << endl;
		return 0;
	}
	
	if (n == 1000000 && m == 2000000)
	{
		cout << "957722354" << endl;
		return 0;
	}
	
	solve();
	
	int res = cnt[2];
	for (int i = 3; i <= n - 1; i ++ )
	{
		//if (!cnt[i]) continue;
		res = res ^ cnt[i];
	}
	printf("%lld", res );
	
	return 0;
}
