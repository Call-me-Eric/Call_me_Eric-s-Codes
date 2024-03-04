#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5e4 + 0721;
int val[N];
ll f[N];
int a[N], b[N], c[N], d[N], e[N], lst[N];
int n;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

int main() {
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read(), b[i] = read(), c[i] = read(), d[i] = read(), e[i] = read(), val[i] = read();
	for (int i = 1; i <= n; ++i) {
		f[i] = val[i];
		ll maxn = 0;
		for (int j = i - 1; j; --j) 
			if ((a[j] <= a[i]) & (b[j] <= b[i]) & (c[j] <= c[i]) & (d[j] <= d[i]) & (e[j] <= e[i])) maxn = max(maxn, f[j]);
		f[i] += maxn;
	}
	
	for (int i = 1; i <= n; ++i) printf("%lld\n", f[i]);
	
	return 0;
}
