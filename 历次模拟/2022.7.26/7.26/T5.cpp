#include<stdio.h>
#define int long long
using namespace std;
int n, T, s;
const int maxn = 550000;
int c[5], dp[maxn], d[5];
int f(int id){
	return c[id] * (d[id] + 1);
}
signed main(){
	scanf("%lld%lld%lld%lld%lld",&c[1],&c[2],&c[3],&c[4],&n);
	dp[0] =  1;
	for(int i = 1;i <= 4;i++){
		for(int j = c[i];j <= maxn;j++){
			dp[j] += dp[j - c[i]];
		}
	}
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld%lld%lld%lld",&d[1],&d[2],&d[3],&d[4],&s);
		int ans = dp[s];
		for(int i = 1;i <= 4;i++)if(s >= f(i))ans -= dp[s - f(i)];
		if(s >= f(1) + f(2))ans += dp[s - f(1) - f(2)];
		if(s >= f(1) + f(3))ans += dp[s - f(1) - f(3)];
		if(s >= f(1) + f(4))ans += dp[s - f(1) - f(4)];
		if(s >= f(2) + f(3))ans += dp[s - f(2) - f(3)];
		if(s >= f(2) + f(4))ans += dp[s - f(2) - f(4)];
		if(s >= f(3) + f(4))ans += dp[s - f(3) - f(4)];
		if(s >= f(1) + f(2) + f(3))ans -= dp[s - f(1) - f(2) - f(3)];
		if(s >= f(1) + f(2) + f(4))ans -= dp[s - f(1) - f(2) - f(4)];
		if(s >= f(1) + f(3) + f(4))ans -= dp[s - f(1) - f(3) - f(4)];
		if(s >= f(2) + f(3) + f(4))ans -= dp[s - f(2) - f(3) - f(4)];
		if(s >= f(1) + f(2) + f(3) + f(4))ans += dp[s - f(1) - f(2) - f(3) - f(4)];
		printf("%lld\n",ans);
	}
	return 0;
}

