#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3 ) + (ch ^ 48);ch = getchar();}
	return x * f;
}
inline void write(int x){if(!x)return;write(x / 10);putchar('0' + (x % 10));}
const int maxq = 5e5 + 10, mod = 998244353;
int q, m;
int f[maxq * 100];
int qpow(int x,int a){
	int res = 1;
	while(a){
		if(a & 1)res = (res * x) % m;
		x = (x * x) % m;a >>= 1;
	}
	return res;
}
int solve(){
	if(m == 1)return 1;
	memset(f,0,sizeof(f));
	for(int x = 0;x < m;x++){
		for(int a = 1;a <= m;a++){
			if(qpow(x,a) == 1){f[a]++;break;}
		}
	}
	int ans = 0;
	for(int i = 1;i <= m;i++){
		ans = max(ans,f[i]);
	}
	return ans % mod;
}
signed main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	m = 1;q = read();int u;
	while(q--){
		u = read();
		if(u > 0)m *= u;
		else m /= (-u);
		printf("%lld\n",solve());
	}
	return 0;
}
