#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int mod = 1e9 + 7, maxn = 2e3 + 10;
int f[maxn][maxn], n, a[maxn];
int qpow(int x,int a){
	int res = 1;
	while(a){
		if(a & 1)res = res * x % mod;
		x = x * x % mod;a >>= 1;
	}
	return res;
}
struct BIT{
	int c[maxn];
	inline int lowbit(int x){return x & (-x);}
	void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] = (c[x] + add) % mod;}
	int qry(int x){int ans = 0;for(;x;x -= lowbit(x));ans = (ans + c[x]) % mod;return ans;}
	int qry(int l,int r){return (qry(r) - qry(l - 1) + mod) % mod;}
}T[maxn],t1[maxn],t2[maxn];
signed main(){
	n = read() + 2; a[1] = 1; a[n] = n;
	for(int i = 2;i <= n - 1;i++)a[i] = read() + 1;
	for(int l = n - 1;l;l--){
		for(int r = l + 1;r <= n;r++){
			int inv = T[l].qry(a[l] + 1,a[r] - 1);
			if(inv)f[l][r] = ((t1[l].qry(a[l] + 1,a[r] - 1) + t2[r].qry(a[l] + 1,a[r] - 1)) * qpow(inv,mod - 2) % mod + 1) % mod;
			T[l].upd(a[r],1);t1[l].upd(a[r],f[l][r]);t2[r].upd(a[l],f[l][r]);
		}
	}
	printf("%lld\n",f[1][n]);
	return 0;
}
