#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define TT int
using namespace std;
inline TT read() {
	TT x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') f = -1; ch = getchar(); }
	while(ch <= '9' && ch >= '0') {x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
const int maxn = 1e6 + 10;
int n;
int a[maxn], b[maxn];
signed main() {
	n = read();
	for(int i = 1;i <= n;i++){
		b[i] = a[i] = read();
	}
	sort(b + 1,b + 1 + n);
	int sum1 = 0, sum2 = 0, ans = 0;
	for(int i = 1;i <= n;i++){
		sum1 += a[i];
		sum2 += b[i];
		if(sum1 == sum2)ans++;
	}
	printf("%d\n",ans);
	return 0;
}

