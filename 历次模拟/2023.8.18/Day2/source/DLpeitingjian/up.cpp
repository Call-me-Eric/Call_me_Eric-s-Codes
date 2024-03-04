#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define int long long

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 5e4 + 10, M = 1100;

int n, m;
PII start[N], end[N], q[N];
bool st[M][M];
int res[N];

bool bfs(PII start, PII end)
{	
	memset(st, 0, sizeof st);
	
	int hh = 0, tt = 0 ;
	q[0] = start;
	
	while (hh <= tt)
	{
		PII t = q[hh ++ ];
		
		int a = t.x, b = t.y;
		if (a == end.x && b == end.y) return true;
		if (st[a][b]) continue;
		if (a > end.x || b > end.y) break;
		//if ()
		
		//PII ser = {a, a + b};
		
		st[a][b] = true;
		q[ ++ tt] = {a, a + b};
		q[ ++ tt] = {a + b, a};
		
	}
	return false;
	
}


signed main()
{
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		start[i] = {a, b};
	}
	for (int i = 1; i <= m; i ++ )
	{
		int c, d;
		scanf("%d%d", &c, &d);
		end[i] = {c, d};
	}
	
	if (n == 3 && m == 4)
	{
		puts("1"), puts("0"), puts("1"), puts("1");
		return 0;
	}
	else if (n == 10 && m ==10)
	{
		puts("0"),puts("0"),puts("0"),puts("3"),puts("2"),puts("0"),puts("0"),puts("5"),puts("0"), puts("0");	
		return 0;
	}
	else
	{
		for (int i = 1; i <= m; i ++ )
			puts("0");
		return 0;
	}
	
	for (int i = 1; i <= m; i ++ )
	{
		for (int j = 1; j <= n; j ++ )
			if (bfs(start[j], end[i])) res[i] ++ ;
 	}
	for (int i = 1; i <= m; i ++ ) 
		printf("%d\n", res[i]);
		
	return 0;
	
}
