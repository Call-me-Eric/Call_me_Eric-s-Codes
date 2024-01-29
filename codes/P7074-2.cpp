#include<cstdio>
#include<cstdlib>
#include<iostream>
#define Max(a,b) a > b ? a : b
using namespace std;
long long dp[2][1001][1001];//0是上下走，1是从左往右走 
int n, m;
long long a[1001][1001];
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	dp[0][1][1] = dp[1][1][1] = a[1][1];
	for(int i = 2;i <= n;i++)dp[1][i][1] = a[i][1] + dp[1][i - 1][1];
	for(int j = 2;j <= m;j++){
		dp[1][1][j] = dp[0][1][j] = Max(dp[1][1][j - 1], dp[0][1][j - 1]) + a[1][j];
		for(int i = 2;i <= n;i++){
			dp[0][i][j] = a[i][j] + Max(dp[0][i][j - 1],dp[1][i][j - 1]);
			dp[1][i][j] = Max(dp[0][i][j],a[i][j] + dp[1][i - 1][j]);
		}
		for(int i = m;i >= 2;i--){
			dp[0][i][j] = Max(dp[0][i][j],dp[0][i + 1][j] + a[i][j]);
		}
	}
	printf("%lld",Max(dp[0][n][m],dp[1][n][m]));
	return 0;
}

