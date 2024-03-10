#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define int long long
using namespace std;
const int mod = 30011;
const int maxM = 111;
struct M{
	int a[maxM][maxM];
	void clear(){
		for(int i = 0;i < maxM;i++){
			for(int j = 0;j < maxM;j++){
				a[i][j] = 0;
			}
		}
	}
};
int n, m;
M operator * (M a,M b){
	M c;
	c.clear();
	for(int i = 1;i <= n * 2;i++){
		for(int j = 1;j <= n * 2;j++){
			for(int k = 1;k <= n * 2;k++){
				c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
			}
		}
	}
	return c;
}
M qpow(M tmp,int llll){
	M res;
	res.clear();
	for(int i = 1;i <= n * 2;i++) res.a[i][i] = 1;
	while(llll){
		if(llll & 1)res = res * tmp;
		tmp = tmp * tmp;
		llll >>= 1;
	}
	return res;
}
signed main(){
	M base;
	scanf("%lld%lld",&n,&m);
	if(m == 2){
		if(n == 1 || n == 2){
			puts("1");
			return 0;
		}
		else{
			puts("0");
			return 0;
		}
	}
	else if(m == 3){
		if(n == 1 || n == 3){
			puts("1");
			return 0;
		}
		if(n == 2){
			puts("2");
			return 0;
		}
		else{
			puts("0");
			return 0;
		}
	}
	base.clear();
	for(int i = 1;i <= n;i++){
		for(int j = max(i - 1,1ll);j <= min(i + 1,n);j++){
			base.a[i][j] = 1;
		}
	}
	for(int i = 1;i <= n;i++){
		base.a[i + n][i] = base.a[i][i + n] = 1;
	}
	base = qpow(base,m - 2);
	if(n == 1)printf("%lld\n",(base.a[2 * n][1] + base.a[2 * n][2]) % mod);
	else if(n == 2)printf("%lld\n",(base.a[2 * n][1] * 2 + base.a[2 * n][2] * 2 + base.a[2 * n][3] + base.a[2 * n][4]) % mod);
	else printf("%lld\n",( base.a[2*n][1]*2+base.a[2*n][2]*2+base.a[2*n][3]+base.a[2*n][n+1]+base.a[2*n][n+2]+mod) % mod);
	return 0;
}
