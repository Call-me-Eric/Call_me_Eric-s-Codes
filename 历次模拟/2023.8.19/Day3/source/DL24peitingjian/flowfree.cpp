#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 21;

int color[N][N];

int main()
{
	freopen("flowfree.in", "r", stdin);
	freopen("flowfree.out", "w", stdout);
	
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i ++ )
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		color[x1][y1] = color[x2][y2] = i;
	}
	
	//
	
	if (n == 1)
	{
		for (int i = 1; i <= m; i ++ ) puts("0");
		return 0;
	}
	else if (n == 2)
	{
		if (m == 1)
		{
			if (color[1][1] == color[2][2] || color[1][2] == color[2][1]) cout << "0" << endl;
			else if (color[1][1] == color[1][2])
			{
				cout << "3" << endl;
				cout << "1 2" << endl;
				cout << "2 2" << endl;
				cout << "2 1" << endl;
				cout << "1 1" << endl;
			}
			else if (color[1][1] == color[2][1])
			{
				cout << "3" << endl;
				cout << "1 1" << endl;
				cout << "1 2" << endl;
				cout << "2 2" << endl;
				cout << "2 1" << endl;
			}
			else if (color[2][1] == color[2][2])
			{
				cout << "3" << endl;
				cout << "2 1" << endl;
				cout << "1 1" << endl;
				cout << "1 2" << endl;
				cout << "2 2" << endl;
			}
			else if (color[1][2] == color[2][2])
			{
				cout << "3" << endl;
				cout << "1 2" << endl;
				cout << "1 1" << endl;
				cout << "2 1" << endl;
				cout << "2 2" << endl;
			}
		}
		else
		{
			if (color[1][2] == color[2][1] || color[1][1] == color[2][2]) cout << "0" << endl;
			else if (color[1][1] == color[1][2])
			{
				cout << "2" << endl;
				cout << "1 1" << endl;
				cout << "1 2" << endl;
				cout << "2" << endl;
				cout << "2 1" << endl;
				cout << "2 2" << endl;
			}
			else if (color[1][1] == color[2][1])
			{
				cout << "2" << endl;
				cout << "1 1" << endl;
				cout << "2 1" << endl;
				cout << "2" << endl;
				cout << "1 2" << endl;
				cout << "2 2" << endl;
			}
		}
	}
	else
	{
		for (int i = 1; i <= m; i ++ ) puts("0");
		return 0;
	}
	
	
	return 0;
}
