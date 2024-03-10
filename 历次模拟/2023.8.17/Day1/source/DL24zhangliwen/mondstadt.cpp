#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

inline int read(void) {
	int x = 0, c = getchar(); 
	while (!isdigit(c)) c = getchar(); 
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x; 
}

inline int poww(int a, int b) {
	int r = 1; 
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
	return r; 
}

int n, m; 
int deg[1000005], cnt[1000005]; 
int fac[1000005], ifac[1000005]; 
inline int C(int n, int m) { return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P; }

int main(void) {
	freopen("mondstadt.in", "r", stdin); 
	freopen("mondstadt.out", "w", stdout); 
	n = read(), m = read(); 
	for (int i = fac[0] = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P; 
	ifac[n] = poww(fac[n], P - 2); 
	for (int i = n - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 
	while (m--) {
		int u = read(), v = read(); 
		++deg[u]; ++deg[v]; 
	}
	for (int u = 1; u <= n; ++u)
		for (int i = 2; i <= deg[u]; ++i)
			cnt[i] = (cnt[i] + C(deg[u], i)) % P;  
	int ans = 0; 
	for (int i = 2; i < n; ++i) ans ^= cnt[i]; 
	printf("%d\n", ans); 
	return 0; 
}
