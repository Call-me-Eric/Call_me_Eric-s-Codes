#include <iostream>
#include <cstdio>

#define i64 long long

using namespace std;

const i64 MOD = 4294967296;

int n, m;
char s[50005];
int sum[50005];

inline int query(int x, int y)
{
	return sum[y] - sum[x - 1];
}

int main(void)
{
	freopen("0w0.in", "r", stdin);
	freopen("0w0.out", "w", stdout);
	scanf("%d%d%s", &n, &m, s + 1);
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + (s[i] == '0');
	while (m--)
	{
		char c, w;
		int x, y;
		cin >> c;
		if (c == 'A')
		{
			scanf("%d", &x); cin >> w;
			if (s[x] != '0' && w == '0')
			{
				for (int i = x; i <= n; ++i)
					++sum[i];
			}
			else if (s[x] == '0' && w != 0)
			{
				for (int i = x; i <= n; ++i)
					--sum[i];
			}
			s[x] = w;
		}
		else if (c == 'B')
		{
			scanf("%d%d", &x, &y); cin >> w;
			for (int i = x; i <= y; ++i)
				s[i] = w;
			for (int i = 1; i <= n; ++i)
				sum[i] = sum[i - 1] + (s[i] == '0');
		}
		else
		{
			scanf("%d%d", &x, &y);
			i64 ans = 0;
			for (int i = x; i < y - 3; ++i)
			  if (s[i] == '(')
				for (int j = i + 2; j < y - 1; ++j)
				  if (s[j] == 'w')
					for (int k = j + 2; k <= y; ++k)
					  if (s[k] == ')')
					  {
					    int a = query(i + 1, j - 1), b = query(j + 1, k - 1);
					    ans = (ans + (i64)a * b) % MOD;
					  }		
			printf("%lld\n", ans);
		}
	}
	return 0;
}
