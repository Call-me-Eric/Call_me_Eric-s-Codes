#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 1e3 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int T, n, m;
int ans[N];
int a[N];
int All;
int qpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int inv(int x) {
	return qpow(x, mod - 2);
}
void dfs(int ct) {
	if(ct == m + 1) {
		All++;
		int cnt = 0;
		for(int i = 1; i <= n; i++) if(a[i] != i) cnt++;
		ans[cnt]++;
		return ;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			swap(a[i], a[j]);
			dfs(ct + 1);
			swap(a[i], a[j]);
		}
}
signed main() {
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	T = read();
	while(T--) {
		n = read(), m = read();
		for(int i = 1; i <= n; i++) a[i] = i;
		All = 0;
		memset(ans, 0, sizeof(ans));
		dfs(1);
//		printf("%lld\n", All);
//		for(int i = 1; i <= n; i++) printf("%lld: %lld\n", i, ans[i]);
		int res = 0;
		for(int i = 1; i <= n; i++) res += ans[i] * i;
//		printf("%lld\n", res);
		printf("%lld\n", res * inv(All) % mod);
	}
	return 0;
}

