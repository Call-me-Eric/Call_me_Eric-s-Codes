#include <bits/stdc++.h> 
#define int long long
using namespace std;

const int N = 3e5 + 3e4;
int s[N], atk[N], pre[N];
int m, T;

signed main()
{
	freopen("dark.in", "r", stdin);
	freopen("dark.out", "w", stdout);
	cin >> m >> T;
	s[1] = 134775813 % m;
	atk[1] = (s[1] & 1) ? 4 : ((s[1] >> 1) & 1) ? 3 : 1;
	pre[1] = atk[1];
	for(int i = 2; i <= 3e5; i = i + 1)
	{
		s[i] = (1103515245 * s[i - 1] + 1013904223) % m;
		atk[i] = (s[i] & 1) ? 4 : ((s[i] >> 1) & 1) ? 3 : 1;
		pre[i] = pre[i - 1] + atk[i];
	}
	while(T --)
	{
		int l, r;
		cin >> l >> r;
		int ans = 0;
		for(int i = l; i <= r; i = i + 1)
			for(int j = i; j <= r; j = j + 1)
				if((pre[j] - pre[i - 1]) > 3 * (j - i + 1))
					ans ++;
		cout << ans << "\n"; 
	}
	return 0;
}
