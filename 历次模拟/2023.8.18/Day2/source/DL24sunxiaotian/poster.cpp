#include <bits/stdc++.h>
#define ll long long
using namespace std;

int T;
const int mod = 998244353;
ll n, m;

inline ll read() {
	ll xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9')
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

ll ksm(ll x, ll y) {
	if (x == 0) return 0;
	ll ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

int main() {
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	
	scanf("%d", &T);
	while (T--) {
		n = read(), m = read();
		ll fz = 2 * (n - 1);
		ll fm = n;
//		cout <<fz << " " << fm << " ";
		ll res = fz * ksm(fm, mod - 2) % mod;
		
		printf("%lld\n", ksm(res, m));
	}
	
	return 0;
}
