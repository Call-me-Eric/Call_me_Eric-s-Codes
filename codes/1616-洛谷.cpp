#include <cstdio>
#include <iostream>
using namespace std;
int n, m;
int dp[100001];
int w[10001], c[10001]; 
int main() {
	scanf("%d%d",&m,&n);
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
	printf("%d",dp[m]);
	return 0;
}

