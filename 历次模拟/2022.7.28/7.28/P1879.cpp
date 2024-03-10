#include<bits/stdc++.h>
using namespace std;
int m, n;
int dp[20][1<<13];
int a[20], x;
bool book[1 << 13];
const int mod = 100000000;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&x);
			a[i] = (a[i] << 1) + x;
		}
	}
	for(int i = 0;i < (1 << m);i++){
		book[i] = ((i & (i << 1)) == 0) && ((i & (i >> 1))== 0);
	}
	dp[0][0] = 1;
	for(int i = 1;i <= n;i++){
		for(int j = 0;j < (1 << m);j++){
			if(book[j] && (j & a[i]) == j){
				for(int k = 0;k < (1 << m);k++){
					if((k & j) == 0){
						dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
					}
				}
			}
		}
	}
	int ans = 0;
	for(int j = 0;j <= (1 << m);j++){
		ans = (ans + dp[n][j]) % mod;
	}
	printf("%d\n",ans);
	return 0;
}
