#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int dp[31][31];
int n, m;
long long ans;
int main(){
	scanf("%d%d",&n,&m);
	dp[0][1] = 1;
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= n;j++){
			if(j == 1){
				dp[i][j] = dp[i - 1][n] + dp[i - 1][2];
			}
			else if(j == n){
				dp[i][j] = dp[i - 1][n - 1] + dp[i - 1][1];
			}
			else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
		}
	}
	printf("%d",dp[m][1]);
	return 0;
}

