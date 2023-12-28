#include <bits/stdc++.h>

using namespace std;

const int N = 300010;

int n, m;
int a[N];
bool st[N];

signed main()
{
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	while (m -- )
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int res = 0;
		for (int j = 1; j <= r - l + 1; j ++ )
			for (int i = l; i + j - 1 <= r; i ++ )
			{
				int maxv = 0;
				memset(st, 0, sizeof st);
				for (int k = 1; k <= i - 1; k ++ ) st[a[k]] = true;
				for (int k = i + j; k <= n; k ++ ) st[a[k]] = true;
				for (int k = i; k <= i + j - 1; k ++ )	if (!st[a[k]]) maxv = max(maxv, a[k]);
				res += maxv;
			}
		cout << res << '\n';
	}
	return 0;
}
