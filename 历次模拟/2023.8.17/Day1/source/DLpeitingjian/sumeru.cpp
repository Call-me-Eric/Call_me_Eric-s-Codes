#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int T;
	cin >> T;
	while (T -- )
	{
		int a11, a12, a13;
		int a21, a22, a23;
		int a31, a32, a33;
		int a41, a42, a43;
		cin >> a11 >> a12 >> a13 >> a21 >> a22 >> a23 >> a31 >> a32 >> a33 >> a41 >> a42 >> a43;
		
		int A1 = a11 + a12 + a13;
		int A2 = a21 + a22 + a23;
		int A3 = a31 + a32 + a33;
		int A4 = a41 + a42 + a43;
		
		//int p1 = A1, p2 = A2, p3 = A3;
		//int p4 = A1 + A2, p5 = A1 + A3, p6 = A2 + A3, p7 = A1 + A2 + A3;
		if (A4 == 0)
		{
			puts("NO");
			continue;
		}
		else
		{
			bool st = false;
			
			for (int i = 0; i <= 98; i ++ )
				for (int j = 0; j <= 98; j ++ )
					for (int k = 0; k <= 98; k ++ )
						if (A1 * i + A2 * j + A3 * k == A4)
						{
							st = true;
							break;
						}
			if (st) puts("YES");
			else puts("NO");
			
		}
	}
	
	return 0;
}
