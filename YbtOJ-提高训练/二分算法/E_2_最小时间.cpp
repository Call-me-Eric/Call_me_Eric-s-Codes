#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
int n, m, S;
const int maxn = 1e6 + 10, maxtime = 1e9;
int k[maxn], b[maxn], a[maxn];
int sum = 0;
bool check(int mid){
	for(int i = 1;i <= n;i++){a[i] = k[i] * mid + b[i];}
	nth_element(a + 1,a + m,a + 1 + n,greater<int>());
	int sum = 0;for(int i = 1;i <= m;i++){if(a[i] >= 0 && (sum += a[i]) >= S)return true;}
	return false;
}
signed main(){
	n = read(); m = read(); S = read();
	for(int i = 1;i <= n;i++){k[i] = read(); b[i] = read(); sum += b[i];}
	if(check(0)){puts("0");return 0;}
	int l = 1, r = maxtime,ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid))r = mid - 1,ans = mid;
		else l = mid + 1;
	}
	printf("%lld\n",ans);
	return 0;
}
