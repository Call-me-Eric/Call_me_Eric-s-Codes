#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int dp[25][85];
int v, u, k;
int c[1005], a[1005], b[1005]; 
int main() {
	memset(dp,127,sizeof(dp));
	dp[0][0] = 0;
	scanf("%d%d",&v,&u);
	scanf("%d",&k);
	for(int i = 1;i <= k;i++){
		scanf("%d%d%d",&a[i], &b[i], &c[i]);
	}
	int t1 = 0, t2 = 0;
	for(int i = 1;i <= k;i++){
		for(int j = v;j >= 0;j--){
			for(int l = u;l >= 0;l--){
				t1 = j + a[i];
				t2 = l + b[i];
				if(t1 > v)	t1 = v;
				if(t2 > u)	t2 = u;
				if(dp[t1][t2] > dp[j][l] + c[i])
					dp[t1][t2] = dp[j][l] + c[i];
			}
		}
	}
	printf("%d",dp[v][u]);
	return 0;
}

