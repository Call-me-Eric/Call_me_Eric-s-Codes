#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int dp[6005];
int w[505], v[505], s[505];
int N, M;
int main() {
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= N;i++){
		scanf("%d%d%d",&v[i],&w[i],&s[i]);
	}
	for(int i = 1;i <= N;i++){
		for(int j = M;j >= 1;j--){
			for(int k = 1;k <= s[i];k++){
				if(j < k * v[i])break;
				dp[j] = max(dp[j],dp[j - v[i] * k] + w[i] * k);
			}
		}
	}
	printf("%d",dp[M]);
	return 0;
}
