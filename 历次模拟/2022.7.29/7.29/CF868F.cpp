#include<iostream>
#include<stdio.h>
#include<string.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int buc[maxn], L, R, a[maxn];
int n, m;
ll dp[21][maxn];
int cur;
ll ans;
void update(int c,int d){
	ans += d * buc[c] * (ll)(buc[c] - 1) / 2;
	return;
}
ll cal(int l,int r){
	while(L < l){
		update(a[L],-1);
		buc[a[L]]--;
		update(a[L],1);
		L++;
	}
	while(L > l){
		L--;
		update(a[L],-1);
		buc[a[L]]++;
		update(a[L],1);
	}
	while(R < r){
		R++;
		update(a[R],-1);
		buc[a[R]]++;
		update(a[R],1);
	}
	while(R > r){
		update(a[R],-1);
		buc[a[R]]--;
		update(a[R],1);
		R--;
	}
	return ans;
}
void solve(int lb,int rb,int l,int r){
	if(lb > rb || l > r)return;
	int mid = l + r >> 1;
	int d = 0;
	ll res = 1e18;
	for(int i = lb;i <= rb;i++){
		ll tmp = cal(i + 1,mid);
		if(res > dp[cur - 1][i] + tmp){
			res = dp[cur - 1][i] + tmp;
			d = i;
		}
	}
	dp[cur][mid] = res;
	solve(lb,d,l,mid - 1);
	solve(d,rb,mid + 1,r);
}
signed main(){
	memset(dp,0x3f,sizeof(dp));
	dp[0][0] = 0;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	buc[a[1]]++;
	L = R = 1;
	for(cur = 1;cur <= m;cur++){
		solve(0,n - 1,1, n);
	}
	printf("%lld\n",dp[m][n]);
	return 0;
}

