#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 0; char ch = getchar();
	while(ch < '0' or ch > '9') f |= (ch == '-'), ch = getchar();
	while(ch >= '0' and ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
int __stk[128], __top;
inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
	do { __stk[++__top] = x % 10, x /= 10; } while(x);
	while (__top) putchar(__stk[__top--] + '0');
}
bool stmer;
const int N = 1e6 + 10, mod = 1e9 + 7;
void add(int &x, int y) { (x += y) >= mod and (x -= mod); }
void mul(int &x, int y) { x = 1ll * x * y % mod; }
int q_pow(int x, int k) {
    int res = 1;
    for(; k; k >>= 1, mul(x, x))
        if(k & 1) mul(res, x);
    return res;
}

int n, k, sum, ans;
int fac[N], inv[N], f[N];

int C(int x, int y) { return 1ll * fac[x] * inv[x - y] % mod * inv[y] % mod;}
bool edmer;
signed main() {
	freopen("arisu.in", "r", stdin);
	freopen("arisu.out", "w", stdout);
	cerr << "[Memory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
	n = read(), k = read(), fac[0] = f[0] = sum = 1;

    for(int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[n] = q_pow(fac[n], mod - 2), ans = fac[n - 1];
    for(int i = n; i; i--) inv[i - 1] = 1ll * inv[i] * i % mod;

    for(int i = 1; i < n; i++) {
        f[i] = 1ll * fac[i - 1] * sum % mod, add(sum, 1ll * inv[i] * f[i] % mod);
        add(ans, 1ll * C(n - 1, i) * f[i] % mod * fac[n - i - 1] % mod);
        if(i >= k) add(sum, mod - 1ll * inv[i - k] * f[i - k] % mod);
    } 
    
    ans = (fac[n] - ans + mod) % mod, write(ans);
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds";
	return 0;
} 