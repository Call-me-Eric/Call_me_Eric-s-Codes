#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define ll long long
using namespace std;
int n;
const ll mod = 1e9 + 7;
bool book[2020];
ll a[2020],f[2020];
ll q, p, pow[4020];
ll qpow(long long a,ll x){
	if(x < 0)return 0;
	if(a == 1)return 1;
	long long res = 1;
	while(x){
		if(x & 1) res = res * a % mod;
		x >>= 1;
		a = a * a % mod;
	}
	long long tmp = mod;
	return res % tmp;
}
ll C(ll n,ll m){
	if(m > n)return 1;
	return pow[n] * qpow(pow[m],mod - 2) % mod * qpow(pow[n - m],mod - 2) % mod;
}
signed main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		if(a[i] == -1)p++;
		else book[a[i]] = 1;
	}
	pow[0] = 1;
	for(int i = 1;i <= n * 2;i++)pow[i] = pow[i - 1] * i % mod;
	for(int i = 1;i <= n;i++){
		if(a[i] == -1 && !book[i])q++;
	}
	for(int i = 1;i <= q;i++){
		f[i] = C(q,i) * pow[p - i] % mod;
	}
	ll ans = pow[p];
	for(int i = 1;i <= q;i++){
		ans = (ans + f[i] * (i & 1 ? -1 : 1)) % mod;
	}
	printf("%lld\n",(ans % mod + mod) % mod);
	return 0;
}

