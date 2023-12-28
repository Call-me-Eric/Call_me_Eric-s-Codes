#include <algorithm>
#include <cstdio>
#include <random>
int n, m, k, ans = 1e9, arr[100005], idx[100005];
inline bool calc(int x, int lim)
{
	int cnt = 0, cur = 0;
	for (int i = 0; i < n && cnt <= k; i++)
	{
		int val = arr[i] + x;
		if (val >= m)
			val -= m;
		if (val > lim)
		{
			cnt = k + 1;
			break;
		}
		cur += val;
		if (cur > lim)
		{
			cur = val;
			cnt++;
		}
	}
	return cnt + !!cur <= k;
}
int main()
{
	
	freopen("monster.in","r",stdin);
	freopen("monster.out","w",stdout);
	
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);
	for (int i = 0; i < m; i++)
		idx[i] = i;
	std::mt19937 rand(std::random_device{}());
	std::shuffle(idx, idx + m, rand);
	for (int i = 0; i < m; i++)
	{
		int x = idx[i], l = 0, r = ans - 1;
		if (!calc(x, ans - 1))
			continue;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (calc(x, mid))
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}

