#include <cstdio>
#include <iostream>
using namespace std;
int a[101], dp[101][10001];
int main() {
	int n ,m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	/*for (int i = 0; i <= n; i++) dp[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++){
			//dp[i][j]表示前i道菜恰好花费j元的方案数 
			dp[i][j] += dp[i-1][j];
			if(j >= a[i])
				dp[i][j] += dp[i-1][j-a[i]];
		}
		*/
	for (int i= 1; i <= n; i++)
		for (int j= 1; j <= m; j++){
			if(j == a[i])	dp[i][j] = dp[i-1][j] + 1;
			if(j < a[i])	dp[i][j] = dp[i-1][j];
			if(j > a[i])	dp[i][j] = dp[i-1][j] + dp[i-1][j - a[i]];
		}
	cout << dp[n][m] << endl;
	return 0;
}

