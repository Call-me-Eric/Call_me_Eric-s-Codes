#include <cstdio>
#include <iostream>
using namespace std;
int n, m;
int dp[1001];
int w[101], c[101]; 
int main() {
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&w[i],&c[i]);
	}
	for(int i = 1;i <= n;i++){
		for(int j = m;j >= 0;j--){
			if(j >= w[i]){
				dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
			}
		}
	}
	printf("%d",dp[m]);
	return 0;
}

