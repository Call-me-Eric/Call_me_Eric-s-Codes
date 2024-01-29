#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int dp[201]; 
int w[201], c[201];
int main() {
	int n, m;
	scanf("%d%d",&m, &n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&w[i],&c[i]);
	}
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= m;j++){
			if(j >= w[i]){
				dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
			}
		}
	}
	printf("max=%d",dp[m]);
	return 0;
}
