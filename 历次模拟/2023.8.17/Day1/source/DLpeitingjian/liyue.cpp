#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1e5 + 10;

int n;
int w[N];

int main()
{
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	
	int Q ;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
	scanf("%d", &Q);
	
	while (Q -- )
	{
		int l, r, cnt = 0;
		scanf("%d%d", &l, &r);
		
		for (int i = l; i <= r; i ++ )
			for (int j = i + 1; j <= r; j ++ )
			{
				double d = sqrt(w[i] + w[j]);
				int p = sqrt(w[i] + w[j]);
				
				if (d - p == 0) cnt ++ ;
				
			}
		printf("%d\n", cnt);
		
	}
	return 0;
	
}
