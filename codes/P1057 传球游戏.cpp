#include <iostream>
#include <cstdio>

using namespace std;
int a[33][33];
int main(){
	ios::sync_with_stdio(false);
	int n , m ;
	cin >> n >> m;
	//a[i][j] 表示传到第i个人手里经过了j次传递的方案数 
	a[1][0] = 1;
	for(int j = 1; j <= m; j++)	
		for(int i = 2; i < n; i++)	{
			a[1][j] = a[2][j-1] + a[n][j-1];
			a[n][j] = a[1][j-1] + a[n-1][j-1];
			a[i][j] = a[i-1][j-1] + a[i+1][j-1];
		}
	cout << a[1][m];
	return 0;
}

