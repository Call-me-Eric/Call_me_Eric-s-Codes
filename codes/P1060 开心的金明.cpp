#include <cstdio>
#include <iostream>
using namespace std;
int v[25], p[26], dp[26][30001];
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> v[i] >> p[i]; 
	for (int i = 1; i <= m; i++)
		for (int j = 0; j <= n; j++){
			if(j < v[i])
				dp[i][j] = dp[i-1][j];
			else
				dp[i][j] = max(dp[i-1][j],dp[i-1][j - v[i]] + p[i] * v[i]);
		}
	cout << dp[m][n] << endl;
	return 0;
}

