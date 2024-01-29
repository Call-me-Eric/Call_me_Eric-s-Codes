#include <cstring>
#include <cstdio>
#define max(a,b) a > b ? a : b
using namespace std;
int t,n,m;
int a[201][201], dp[100001];//dp[i]为花费i￥的最大收益 
int main(){
	scanf("%d%d%d",&t,&n,&m);
	for(int i = 1;i <= t;i++){
		for(int j = 1;j <= n;j++){
			scanf("%d",&a[i][j]);
		}
	} 
	for(int as = 1;as < t;as++){
		memset(dp,0,sizeof(dp));
		for(int i = 1;i <= n;i++){
			for(int j = a[as][i];j <= m;j++){
				dp[j] =
				max(dp[j],dp[j - a[as][i]] + (a[as + 1][i] - a[as][i]));
			}
		}
		m = max(m,dp[m] + m);
	}
	printf("%d",m);
	return 0;
}


