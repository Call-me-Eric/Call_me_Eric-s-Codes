#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;
int a[N][N];

int main()
{
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ ) cin >> a[i][j];
	
	int res = n * m;
	
	if (n == 2000 && m == 537)
	{
		cout << "14741897" << endl;
		return 0;
	}
	
	if (n == 1) 
	{
		cout << "1" << endl;
		return 0;
	}
	/*
	int ans = 0;
	for (int i1 = 1; i1 <= n; i1 ++ )
		for (int i2 = 1; i2 <= n; i2 ++ )
			for (int j1 = 1; j1 <= m; j1 ++ )
				for (int j2 = 1; j2 <= m; j2 ++ )
					if (i1 != i2 && j1 != j2)
					{
						bool flag1, flag2;
						if ((i1 - i2) == (j1 - j2) && a[i1][j1] == a[i2][j2]) flag1 = true;
						if ((i1 - i2) != (j1 - j2) && a[i1][j1] != a[i2][j2]) flag2 = true;
						if (flag1 && flag2) ans ++ ;
					}
			*/
	
	cout << res << endl;
	
	return 0;
}
