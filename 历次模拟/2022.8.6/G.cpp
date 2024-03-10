#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define int long long
#define TT long long
using namespace std;
inline TT read() {
	TT x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') f = -1; ch = getchar(); }
	while(ch <= '9' && ch >= '0') {x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int n , k;
const int maxn = 1010;
int w[maxn];
signed main() {
	n = read(); k = read();
	for(int i = 1;i <= n;i++)w[i] = read();
	sort(w + 1,w + 1 + n);
	long long ans = 0;
	for(int i = n;i >= n - k + 1;i--){
		ans += w[i];
	}
	printf("%lld\n",ans);
	return 0;
}

