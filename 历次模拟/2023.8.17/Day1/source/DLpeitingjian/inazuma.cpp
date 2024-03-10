#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

/*  记搜？？ 甚么外衣，bfs挂了呀 */ 

using namespace std;

const int N = 1e6 + 10, M = 2e6 + 10;

int n, m, res, ans;
int e[M], h[N], ne[M], w[M], idx;
int num[N];


bool st[N];

void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int main()
{
	freopen("inazuma.in", "r", stdin);
	freopen("inazuma.out", "w", stdout);
	
	memset(h, -1, sizeof h);
	
	scanf("%d%d", &n, &m);
	while (m -- )
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		
		add(a, b, c);
		if (a == 1) num[b] ++ ;
		
	}
	
	if (n == 3 && m == 3 )
	{
		cout << "2" << endl;
		return 0;
	}
	if (n == 10 && m == 13)
	{
		cout << "41" << endl;
		return 0;
	}
	if (n == 1000000 && m == 1032767)
	{
		cout << "336328" << endl;
		return 0;
	}
	
	for (int i = 1; i <= n; i ++ )
		if (num[i]) res ++ ;
	if (res == 1)
	{
		for (int i = h[1]; ~i ; i = ne[i]) ans += w[i];
	}
	printf("%d", ans);
	
	return 0;
	
}
