#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int mod = 998244353;
int n, m;
int a[1010];
int ans, res;
int times;

int check(){
	int cnt = 0;
	for(int i = 1;i <= n;i++)cnt += (a[i] != i);
	return cnt % mod;
}
void dfs(int u){
//	times ++;
//	if(times > 1000)return;
	if(u == m + 1){
		ans = (ans + check() ) % mod;
		res++;if(res > mod) res %= mod;
		return;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			swap(a[i],a[j]);
			dfs(u + 1);
			swap(a[i],a[j]);
		}
	}
}

int qpow(int x,int a){
	int tmp = 1;
	while(a){
		if(a & 1)tmp = (tmp * x) % mod;
		x = x * x % mod; a >>= 1;
	}
	return tmp;
}

signed main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
int T = read();
while(T--){
	ans = 0; res = 0;
	n = read(); m = read();
	for(int i = 1;i <= n;i++)a[i] = i;
	dfs(1);
	printf("%lld\n",ans * qpow(res , mod - 2) % mod);
//	printf("ans = %lld res = %lld\n",ans,res);
//	printf("%lld\n",qpow(res,mod - 1));
}
	return 0;
}

