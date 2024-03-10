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
const int N = 5e4 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int T, n;
int f[N];
struct node {
	int a, b, c, d, e, f;
	bool operator>(node t)const {
		return a >= t.a && b >= t.b && c >= t.c && d >= t.d && e >= t.e;
	}
} a[N];
signed main() {
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = {read(), read(), read(), read(), read(), read()};
		for(int j = 0; j < i; j++) if(a[i] > a[j]) f[i] = max(f[i], f[j] + a[i].f);
	}
	for(int i = 1; i <= n; i++) printf("%lld\n", f[i]);
	return 0;
}

