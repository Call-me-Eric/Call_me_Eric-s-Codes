#include <algorithm>
#include <cstring>
#include <cstdio>
using ll = long long;
constexpr int LOG = 23;
int arr[100005];
namespace solver_and
{
	int sum[LOG + 5];
	bool in[100005];
	inline void solve(int n)
	{
		for (int i = 0; i < LOG; i++)
		{
			sum[i] = 0;
			for (int j = 0; j < n; j++)
				sum[i] += arr[j] >> i & 1;
		}
		memset(in, true, n);
		int ans = 0, rem = n;
		for (int i = LOG - 1; i >= 0; i--)
		{
			if (sum[i] < 2)
				continue;
			ans |= 1 << i;
			for (int j = 0; j < n; j++)
			{
				if (!in[j] || (arr[j] >> i & 1))
					continue;
				in[j] = false;
				rem--;
				for (int k = i; k >= 0; k--)
					sum[k] -= arr[j] >> k & 1;
			}
		}
		printf("%d %lld\n", ans, (ll)rem * (rem - 1) / 2);
	}
}
namespace solver_xor
{
	int son[3000005][2], all[3000005];
	inline void solve(int n)
	{
		son[0][0] = son[0][1] = 0;
		for (int i = 0, t_cnt = 0; i < n; i++)
		{
			int u = 0;
			for (int j = LOG - 1; j >= 0; j--)
			{
				int c = arr[i] >> j & 1;
				if (!son[u][c])
				{
					son[u][c] = ++t_cnt;
					son[t_cnt][0] = son[t_cnt][1] = 0;
				}
				u = son[u][c];
			}
			all[u]++;
		}
		int ans = 0;
		ll way = 0;
		for (int i = 0; i < n; i++)
		{
			int res = 0, u = 0;
			for (int j = LOG - 1; j >= 0; j--)
			{
				int c = arr[i] >> j & 1;
				if (son[u][c ^ 1])
				{
					res |= 1 << j;
					u = son[u][c ^ 1];
				}
				else
					u = son[u][c];
			}
			if (ans < res)
			{
				ans = res;
				way = 0;
			}
			if (ans == res)
				way += all[u] - !res;
		}
		printf("%d %lld\n", ans, way / 2);
	}
}
namespace solver_or
{
	int app[1 << LOG];
	inline void solve(int n)
	{
		memset(app, 0, (1 << LOG) << 2);
		for (int i = 0; i < n; i++)
			app[arr[i]]++;
		for (int i = 0; i < LOG; i++)
		{
			for (int j = 0; j < 1 << LOG; j++)
			{
				if (j >> i & 1)
					app[j ^ (1 << i)] += app[j];
			}
		}
		int ans = 0;
		ll way = 0;
		for (int i = 0; i < n; i++)
		{
			int flip = 0;
			for (int j = LOG - 1; j >= 0; j--)
			{
				if (arr[i] >> j & 1)
					continue;
				if (app[flip | (1 << j)])
					flip |= 1 << j;
			}
			if (ans < (arr[i] | flip))
			{
				ans = arr[i] | flip;
				way = 0;
			}
			if (ans == (arr[i] | flip))
				way += app[flip] - !flip;
		}
		printf("%d %lld\n", ans, way / 2);
	}
}
int main()
{
	freopen("bit.in","r",stdin);
	freopen("bit.out","w",stdout);
	int n, tp;
	scanf("%d%d", &n, &tp);
	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);
	if (tp == 1)
		solver_and::solve(n);
	else if (tp == 2)
		solver_xor::solve(n);
	else
		solver_or::solve(n);
	return 0;
}
