#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define maxn 2000000
#define mod 998244353
#define ll long long
using namespace std;
ll n, sum[maxn], g[maxn], f[maxn], ans;
int main(){
	scanf("%lld",&n);
	int lim = (1 << n) - 1;
	f[0] = g[0] = 1;
	for(int i = 1;i <= lim;i <<= 1){
		scanf("%lld",&sum[i]);
	}
	for(int i = 1;i <= lim;i++){
		sum[i] = (sum[i ^ (i & -i)] + sum[i & -i]) % mod;
	}
	for(int i = 1;i <= lim;i++){
		for(int j = i;j ;j ^= (j & -j)){
			if(sum[i ^ (j & -j)] >= 0)f[i] = (f[i] + f[i ^ (j & -j)]) % mod;
			if(sum[i] < 0) g[i] = (g[i] + g[i ^ (j & -j)]) % mod;
		}
	}
	for(int i = 1;i <= lim;i++){
		ans = (ans + sum[i] * f[i] % mod * g[lim ^ i] % mod) % mod;
	}
	printf("%lld\n",(ans % mod + mod) % mod);
	return 0;
}

