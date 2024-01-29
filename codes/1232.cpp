#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1001], dp[1001];
int mmin(int a,int b){return a > b ? b : a;}
int main() {
	int t, n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		memset(dp,0,sizeof(dp));
		for(int i = 1;i <= n;i++){
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + 1 + n);
		dp[1] = a[1];	dp[2] = a[2];
		for(int i = 3; i <= n; i++){
			dp[i] = mmin(a[1] + a[i] + dp[i - 1], a[1] + a[2] + a[2] + a[i] + dp[i - 2]);
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}

