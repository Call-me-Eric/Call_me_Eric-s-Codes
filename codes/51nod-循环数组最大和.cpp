#include<cstring>
#include<cstdio>
using namespace std;
#define ll long long
ll a[1000001];
ll dp[1000001];
ll sum;
int n;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		sum += a[i];
	}
	ll maxx = -9999999990,minn = 9999999990,ans = 0;
	for(int i = 1;i <= n;i++){
		if(dp[i - 1] > 0)dp[i] = dp[i - 1] + a[i];
		else dp[i] = a[i];
		if(dp[i] > maxx)maxx = dp[i];
	}
	memset(dp,0,sizeof(dp));
	for(int i = 1;i <= n;i++){
		if(dp[i - 1] < 0)dp[i] = dp[i - 1] + a[i];
		else dp[i] = a[i];
		if(dp[i] < minn)minn = dp[i];
	}
	minn = sum - minn;
	ans = minn < maxx ? maxx : minn;
	printf("%lld",ans);
	return 0;
}

