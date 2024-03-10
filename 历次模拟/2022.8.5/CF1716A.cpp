#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
int T;
int n, ans;
signed main(){
	T = read();
	while(T--){
		n = read();
		printf("%d ",!(n % 3) ? n / 3 : 1 == n ? 2 : 1 + n / 3);
	}
	return 0;
}

