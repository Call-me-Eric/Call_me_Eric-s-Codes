#include<bits/stdc++.h>
using namespace std;

char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)

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
const int N = 1e5 + 10, M = 110, mod = 998244353;
void add(int &x, int y) { (x += y) >= mod and (x -= mod); }
void mul(int &x, int y) { x = 1ll * x * y % mod; }
int q_pow(int x, int k) {
	int res = 1;
	for(; k; k >>= 1, mul(x, x))
		if(k & 1) mul(res, x);
	return res;
}
int n, m, q, unit, tot, res, K;
int fac[N << 2], inv[N << 2], to[N << 2], a[N], b[N], c[N], ans[N], v[M], f[N];
struct node {
	int l, r, id;
	bool operator < (const node &p) const {
		return l / unit == p.l / unit ? (l / unit & 1 ? r > p.r : r < p.r) : l < p.l;
	}
};
vector<node> op[M];
void add(int x) {
	mul(res, b[x] - c[x]), c[x]++;
}
void del(int x) {
	c[x]--, mul(res, inv[b[x] - c[x]]);
}
bool edmer;
signed main() {
	freopen("slim.in", "r", stdin);
	freopen("slim.out", "w", stdout);
	cerr << "[Memory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
	n = read(), m = read(), q = read();
	for(int i = 1; i <= n; i++) b[a[i] = read()]++;
	int mx = 0;
	for(int i = 1; i <= q; i++) {
		int l = read(), r = read(), k = read();
		if(!to[k]) to[k] = ++tot, v[tot] = k, mx = max(mx, k);
		op[to[k]].push_back({l, r, i});
	}

	inv[0] = inv[1] = 1;
	for(int i = 2; i <= n + mx; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;

	int L = 1, R = 0;
	for(int i = 1; i <= tot; i++) {
		unit = max(1, int (n / sqrt(op[i].size())));
		sort(op[i].begin(), op[i].end()), L = res = f[n] = 1, R = 0;
		for(int j = 1; j <= m; j++) c[j] = 0, b[j] += v[i] - K; K = v[i];
		for(int j = n - 1; j; j--) f[j] = (1ll * m * K % mod + n - j) % mod * f[j + 1] % mod;

		for(node p : op[i]) {
			int l = p.l, r = p.r;
			while(R < r) add(a[++R]); while(L > l) add(a[--L]);
			while(R > r) del(a[R--]); while(L < l) del(a[L++]);
			ans[p.id] = 1ll * f[r - l + 1] * res % mod;
		}
	}

	for(int i = 1; i <= q; i++) write(ans[i]), putchar('\n');
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds";
	return 0;
} 