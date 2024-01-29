#include<cstdio>
#include<bits/stdc++.h>
#define Max(a,b) a > b ? a : b
using namespace std;
long long dp[1001][1001];
int n, m;
long long x[1001], y[1001];//x表示从上向下，y表示从下向上 到(i,j)
long long a[1001][1001]; 
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%lld",&a[i][j]);
			dp[i][j] = INT_MIN;
		}
	}
	dp[1][1] = a[1][1];
	for(int i = 2;i <= n;i++){
		dp[i][1] = dp[i - 1][1] + a[i][1];
	}
	for(int j = 2;j <= m;j++){
		
		x[1] = dp[1][j - 1] + a[1][j];
		for(int i = 2;i <= n;i++){ 
			x[i] = max(dp[i][j - 1], x[i - 1]) + a[i][j];
		}
		
		y[n] = dp[n][j - 1] + a[n][j];
		for(int i = n - 1;i >= 1;i--){
			y[i] = max(dp[i][j - 1], y[i + 1]) + a[i][j];
		}
		for(int i = 1;i <= n;i++){
			dp[i][j] = max(x[i],y[i]);
		}
	}
	printf("%lld",dp[n][m]);
	return 0;
}

