#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define ll long long
using namespace std;
ll n, m;
const int maxm = 2 * 1e5 + 10;
const ll MOD = 998244353;
ll inv[maxm], fac[maxm];
ll qpow(long long a,ll x,ll mod){
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
ll C(ll x,ll y,ll mod){
	ll res = 1;
	for(int i = x;i >= x - y + 1;i--){
		res = res * i % mod;
	}
	for(int i = 1;i <= y;i++){
		int tmp = qpow(i,mod - 2,mod);
		res = res * tmp % mod;
	}
	return res;
}
int main(){
	scanf("%lld%lld",&n,&m);
	if(n == 2){
		puts("0");
		return 0;
	}
	printf("%lld\n",C(m,n - 1,MOD) * (n - 2) % MOD * qpow(2,n - 3,MOD)% MOD);
	return 0;
}

