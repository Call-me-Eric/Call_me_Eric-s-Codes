#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define mod 998244353
#define ll long long
using namespace std;
inline ll read(){
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x * 10 + ch - '0') % mod;ch = getchar();}
	return x * f;
}
ll n, m, a[110],ans[110],cnt;
bool book;
ll qpow(ll x,ll a){
	ll res = 1;
	while(a){
		if(a & 1)res = res * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return res;
}
bool check(ll x){
	ll res = 0;
	for(ll i = n;i >= 1;i--){
		res = ((res + a[i]) * x) % mod;
	}
	res = (res + a[0]) % mod;
	return res == 0;
}
signed main(){
	n = read();
	m = read();
	for(int i = 0;i <= n;i++){
		a[i] = read();
	}
	for(int i = 1;i <= m;i++){
		if(check(i)){
			cnt++;
			ans[cnt] = i;
		}
	}
	printf("%lld\n",cnt);
	for(int i = 1;i <= cnt;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}

