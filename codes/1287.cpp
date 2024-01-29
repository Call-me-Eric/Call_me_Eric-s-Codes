#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int dp[101][101];
int a[101][101];
int n; 
int main() {//21:00
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	dp[1][1] = a[1][1];
	for(int i = 2;i <= n;i++){
		dp[1][i] = dp[1][i - 1] + a[1][i];
		dp[i][1] = dp[i - 1][1] + a[i][1];
	} 
	for(int i = 2;i <= n;i++){
		for(int j = 2;j <= n;j++){
			dp[i][j] = min(dp[i - 1][j],dp[i][j - 1]) + a[i][j];
		}
	}
	printf("%d",dp[n][n]);//21:16
	return 0;
}

