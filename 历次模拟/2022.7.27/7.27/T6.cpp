#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
struct M{
	int a[3][3];
	void clear(){
		for(int i = 0;i <= 2;i++){
			for(int j = 0;j <= 2;j++){
				a[i][j] = 0;
			}
		}
	}
};
int n;
M operator * (M a,M b){
	M c;
	c.clear();
	for(int i = 1;i <= 2;i++){
		for(int j = 1;j <= 2;j++){
			for(int k = 1;k <= 2;k++){
				c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
			}
		}
	}
	return c;
}
M ans,base;
void qpow(int x){
	while(x){
		if(x & 1)ans = ans * base;
		base = base * base;
		x >>= 1;
	}
}
signed main(){
	scanf("%d",&n);
	if(n <= 2){
		puts("1");
		return 0;
	}
	ans.a[1][1] = ans.a[1][2] = 1;
	base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
	qpow(n - 2);
	printf("%d\n",ans.a[1][1] % mod);
	return 0;
}

