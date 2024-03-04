#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
const int maxn = 1e6 * 2 + 10;
bool book[maxn];
int pn,tmp[maxn];
int n ,p ,pr[maxn], a[maxn];
int qpow(int a,int x,int mod){
	int res = 1;
	while(x != 0){
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
int rate(int a,int x){
	int ret = 0;
	while(a){
		ret += a / x;
		a /= x;
	}
	return ret;
}
int main(){
	scanf("%d%d",&n,&p);
	for(int i =2 ;i <= n * 2;i++){
		if(!book[i]){
			pr[++pn] = i;
		}
		for(int j = 1;j <= pn && i * pr[j] <= n * 2;j++){
			book[i * pr[j]] = 1;
			if(i % pr[j] == 0){
				a[i] = pr[j];
				break;
			}
		}
	}
	for(int i = 1;i <= pn;i++){
		tmp[i] = rate(2 * n,pr[i]) - rate(n,pr[i]) - rate(n + 1,pr[i]);
	}
	int ans = 1;
	for(int i = 1;i <= pn;i++){
		ans = 1ll * ans * qpow(pr[i],tmp[i],p) % p;
	}
	printf("%d\n",ans);
	return 0;
}

