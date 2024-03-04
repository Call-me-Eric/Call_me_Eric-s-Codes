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
//
int qpow(int x,int a){
	int tmp = 1;x %= mod;
	while(a){
		if(a & 1)tmp = (tmp * x) % mod;
		x = x * x % mod; a >>= 1;
	}
	return tmp;
}

signed main(){
//	freopen("poster.in","r",stdin);
//	freopen("poster.out","w",stdout);
int T = read();
while(T--){
	n = read(); m = read();
	int t1 = (mod + 1 - 2ll * qpow(n, mod - 2) % mod) % mod;
	int t = qpow(n,mod - 2);
	int t2 = (qpow(t1,m) * (mod + 1 - t) % mod + t) % mod;
	printf("%lld\n",n % mod * (mod + 1 - t2) % mod);
}
	return 0;
}

