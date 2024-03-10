#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10, maxm = 2e6 + 10, mod = 1e9 + 7;
int n, m;
int d[maxn], cnt[maxn];
int pw[maxm], invpw[maxm];
int qpow(int x,int a){
	int res = 1;
	while(a){
		if(a & 1)res = x * res % mod;
		x = x * x  % mod;
		a >>= 1;
	}
	return res;
}
int C(int x,int y){
	if(x < y)return 0;
	return pw[x] * invpw[y] % mod * invpw[x - y] % mod;
}
signed main(){
//	freopen("mondstadt.in","r",stdin);
//	freopen("mondstadt.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= m;i++){
		d[read()]++;d[read()]++;
	}
	pw[0] = 1;
	for(int i = 1;i < maxm;i++)pw[i] = (pw[i - 1] * i) % mod;
	invpw[maxm - 1] = qpow(pw[maxm - 1], mod - 2);
	for(int i = maxm - 2;i;i--)invpw[i] = (invpw[i + 1] * (i + 1) % mod) % mod;
	invpw[0] = 1;
	for(int i = 1;i <= n;i++){
		for(int j = 2;j <= d[i];j++){
//			cnt[j] = (cnt[j] + (d[i] - j + 2) * (d[i] - j + 1) / 2 % mod) % mod;
			cnt[j] = (cnt[j] + C(d[i],j)) % mod;
		}
	}
	int ans = 0;
	for(int i = 2;i < n;i++){
		ans ^= cnt[i];
	}
	printf("%lld\n",ans);
	return 0;
}

