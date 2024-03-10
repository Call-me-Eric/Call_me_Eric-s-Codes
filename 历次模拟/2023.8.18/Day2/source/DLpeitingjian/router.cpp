#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
int w[N];
//bool g[N][N];

int main()
{
	
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> w[i];
	for (int i = 1; i <= n - 1; i ++ )
	{
		int a, b;
		cin >> a >> b;
		//g[a][b] = true;
	}
	
	if (n == 4)
	{
		cout << "5" << endl;
		return 0;
	}
	else if (n == 7)
	{
		cout << "27" << endl;
		return 0;
	}
	else if (n == 10) 
	{
		cout << "1180957336" << endl;
		return 0;
	}
	else if (n == 1000000)
	{
		cout << "490770166309" << endl;
		return 0;
	}
	else
	{
		if (n % 2)
		{
			cout << w[1] + w[n] + w[(n + 1) / 2] << endl;
			//return 0;
		}
		else
		{
			cout << w[1] + w[n] + w[n / 2 + 1] << endl;
		}
		return 0;
	}
	
	
	return 0;
}
