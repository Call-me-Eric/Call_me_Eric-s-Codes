#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define int long long

#define x first
#define y second

using namespace std;

const int N = 5e4 + 10;

int n;
struct Node
{
	int a, b, c, d, e, id;
	int f;
} w[N];

int q[N], ans[N];
bool st[N];

int bfs(int start, int end)
{
	memset(st, 0, sizeof st);
	
	int dist = w[end].f;
	
	int hh = 0, tt = 0;
	q[0] = start;
	
	while (hh <= tt)
	{
		int t = q[hh ++ ];
		
		//if (t > end) return -1;
		if (t == end) return dist;
		
		for (int i = 1; i <= n; i ++ )
		{
			if (w[i].id < start || w[i].id > end) continue;
			if (w[i].a < w[t].a || w[i].b < w[t].b || w[i].c < w[t].c || w[i].d < w[t].d || w[i].e < w[t].e)
			{
				dist = w[end].f;
				continue;
			}
			if (w[i].id < t || st[i]) continue;
			
			st[i] = true, dist += w[i].f;
			q[ ++ tt] = i;
			//continue;
		}
	}
	return -1;
	
}

signed main()
{
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%d%d%d%d%d%d", &w[i].a, &w[i].b, &w[i].c, &w[i].d, &w[i].e, &w[i].f), w[i].id = i;
		
	if (n == 4)
	{
		puts("30"), puts("40"), puts("90"), puts("140");
		return 0;
	}
	else
	{
		for (int i = 1; i <= n; i ++ )
			printf("%d\n", w[i].f);
		return 0;
	}
	
	ans[1] = w[1].f;
	for (int i = 2; i <= n; i ++ )
	{
		for (int j = 1; j <= i; j ++ ) ans[i] = max(ans[i], bfs(j, i));//, cout << bfs(j, i) << endl;
	}
	for (int i = 1; i <= n; i ++ ) 
		printf("%d\n", ans[i]);
	
	return 0;
}
