#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10, maxm = 2e6 + 10, mod = 1e9 + 7;
int n, m;
int d[maxn], cnt[maxn];
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= m;i++){
		d[read()]++;d[read()]++;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 2;j <= d[i];j++){
			cnt[j] = (cnt[j] + (d[i] - j + 2) * (d[i] - j + 1) / 2 % mod) % mod;
		}
	}
	int ans = 0;
	for(int i = 2;i < n;i++){
		ans ^= cnt[i];
	}
	printf("%lld\n",ans);
	return 0;
}

