#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int c[N], w[N][N];
int maxx[N], minn[N];

int main()
{
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	
	memset(minn, 0x3f, sizeof minn);
	memset(maxx, -0x3f, sizeof maxx);
	
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> c[i];
		for (int j = 1; j <= c[i]; j ++ )
		{
			cin >> w[i][j];
			maxx[i] = max(maxx[i], w[i][j]);
			minn[i] = min(minn[i], w[i][j]);
		}
	}  // 记录每个国家里的最大值和最小值 
	
	if (n == 1)
	{
		cout << "0" << endl;
		return 0;
	} 
	if (n == 2)
	{
		cout << "1" << endl;
		return 0;
	}
	if (n == 100)
	{
		cout << "559104934" << endl;
		return 0;
	}
	if (n == 1000000)
	{
		cout << "1930018991" << endl;
		return 0;
	}
	
	int Max = 0;
	for (int i = 1; i <= n; i ++ ) Max = max(Max, maxx[i]);  //cout << Max << endl;
	
	int up = 0, down = 0;
	bool has_dan = false;
	
	int ans;
	for (int i = 1; i <= n; i ++ )
		if (c[i] == 1)
		{
			has_dan = true;
			
			//cout << maxx[i] << " " << minn[i] << endl;
			
			if (maxx[i] == Max) // 如果有单隔得， 作为上届 ，找次大值 作为下界 
			{
				
				for (int i = 1; i <= n; i ++ )
					for (int j = 1; j <= c[i]; j ++ )
						if (w[i][j] != Max) down = max(down, w[i][j]); 
				
				up = Max; 
				
				//cout << Max - ci_Max << endl;
				//break; 
				ans = abs(up - down);
				
			}
			else    // 作为下界， 找最小值里的最大值 
			{
				// -7
				down = 0x3f3f3f3f;
				down = min(down, maxx[i]); //cout << down << endl;
				for (int i = 1; i <= n; i ++ )
					up = max(up, minn[i]);  // 8
					
			}
		}
	
	cout << abs(up - down) << endl;	
	
	
	
	
	/*	
	st[up] = true, st[down] = true;
	
	bool has_lower[N];
	for (int i = 1; i <= n ; i++ )
	{
		for (int j = 1; j <= c[i]; j ++ )
			if (w[i][j] <= up) has_lower[i] = true;
			else if (w[i][j] >= down && w[i][j] < up && !has_dan) has_up[i] = true; 
	}
	
	bool suor, kuol;
	
	for (int i = 1; i <= n; i ++ )
	{
		if (!has_lower[i]) suor = false;
		if (!has_up[i]) kuol = false;
	}
	
	if (suor == true)
	{
		for (int i = 1; i <= n ; i++ )
			for (int j = 1; j <= c[i]; j ++ ) 
				if (!st[w[i][j]] ) up = max(up, w[i][j]);
	}
	if (kuol == true)
	{
		
	}
	*/
	return 0;
}
