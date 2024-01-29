#include<iostream>
#include<cstdio>
using namespace std;
int n;
int mod = 1e9 + 7;
int dp[100001];
int main(){
	scanf("%d",&n);
	dp[1] = 2;
	dp[2] = 4;
	for(int i = 3;i <= n;i++){
		dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
	}
	printf("%d",dp[n]);
	return 0;
}

