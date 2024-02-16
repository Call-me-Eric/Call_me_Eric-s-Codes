#include <bits/stdc++.h>
using namespace std;
const int N = 1.5e5 + 5, MOD = 998244353, L = 32;
int pc[L], n, c[N], u, v, P2[N], siz[N], out[N], in[N], mx[N], vis[N], ans; basic_string <int> adj[N];
int read() {
	int s = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s;
}
int R(int x, int y) { return (x += y) >= MOD ? x - MOD : x; }
struct vec {
	int a[L];
	void clear() {
		memset (a, 0, sizeof a);
	}
	void init(int x, int y = 1) {
		for (int i=0; i<L; i++)
			a[i] = pc[i&x] ? MOD - y : y;
	}
	void trans(int x) {
		for (int i=0; i<L; i++)
			a[i] = pc[i&x] ? MOD - a[i] : a[i];
	}
	vec operator + (const vec &b) const {
		vec c;
		for (int i=0; i<L; i++)
			c. a[i] = R(a[i], b. a[i]);
		return c;
	}
	void operator += (const vec &b) {
		for (int i=0; i<L; i++)
			a[i] = R(a[i], b. a[i]);
	}
	void operator -= (const vec &b) {
		for (int i=0; i<L; i++)
			a[i] = R(a[i], MOD - b. a[i]);
	}
	vec operator * (const vec &b) const {
		vec c;
		for (int i=0; i<L; i++)
			c. a[i] = 1ll * a[i] * b. a[i] % MOD;
		return c;
	}
	void operator *= (const vec &b) {
		for (int i=0; i<L; i++)
			a[i] = 1ll * a[i] * b. a[i] % MOD;
	}
} * f[N], now[N], tmp, ss[N], prod[20], sum;
void dfs(int u, int fa) {
	for (int v : adj[u]) if (v ^ fa)
		dfs(v, u), siz[u] += siz[v] + 1;
	int ci = 0, co = 0;
	for (int v : adj[u]) if (v ^ fa)
		(v > u ? out[++co] : in[++ci]) = v;
	sort (out+1, out+co+1, [] (const int &v, const int &w) { return mx[v] < mx[w]; });
	now[0]. init(0), vis[0] = 1;
	for (int i=1; i<=co; i++) {
		int w = out[i-1], v = out[i];
		ss[0]. clear();
		for (int k=0; k<=mx[v]; k++)
			ss[0] += f[v][k];
		for (int j=1; j<1<<mx[w]+1; j++)
			ss[j] = ss[j^j&-j] + f[v][__lg(j&-j)];
		for (int j=(1<<mx[w]+1)-1; ~j; j--) if (vis[j]) {
			for (int t=(1<<mx[v]+1)-1^j; t; ) {
				int l = t & - t, k = __lg(l); t ^= l;
				for (int _=0; _<L; _++)
					now[j|l]. a[_] = (now[j|l]. a[_] + 1ll * now[j]. a[_] * f[v][k]. a[_]) % MOD;
				// tmp -= f[v][k], now[j|l] += now[j] * f[v][k];
				vis[j|l] = 1;
			} now[j] *= ss[j];
		}
	}
	sort (in+1, in+ci+1, [] (const int &v, const int &w) { return mx[v] < mx[w]; });
	prod[0]. init(0);
	for (int i=1; i<=ci; i++) {
		int w = in[i-1], v = in[i];
		for (int j=mx[w]+1; j<=mx[v]; j++)
			prod[j] = prod[j-1];
		for (int j=0; j<=mx[v]; j++)
			prod[j] *= (f[v][mx[v]] + f[v][j]);
	}
	for (int i=mx[in[ci]]+1; i<=mx[out[co]]+2; i++)
		prod[i] = prod[i-1];
	for (int i=0; i<1<<mx[out[co]]+1; i++) if (vis[i])
		mx[u] = max(mx[u], __builtin_ctz(~ i)); mx[u] += fa > u;
	f[u] = new vec [mx[u]+1] {};
	if (fa < u) {
		for (int i=0; i<1<<mx[out[co]]+1; i++) if (vis[i])
			f[u][__builtin_ctz(~i)] += now[i];
		for (int i=0; i<=mx[u]; i++)
			f[u][i] *= prod[i], c[u] ? f[u][i]. trans(i) : void ();
	} else {
		sum. clear();
		for (int i=0, _, __; i<1<<mx[out[co]]+1; i++) if (vis[i])
			tmp = now[i] * prod[_=__builtin_ctz(~i)], c[u] ? tmp. trans(_) : void (), sum += tmp, f[u][_] -= tmp, 
			tmp = now[i] * prod[__=__builtin_ctz(~i^1<<_)], c[u] ? tmp. trans(__) : void (), f[u][_] += tmp;
		for (int i=0; i<=mx[u]; i++)
			f[u][i] += sum;
	}
	for (int i=0; i<1<<mx[out[co]]+1; i++) if (vis[i])
		now[i]. clear(), vis[i] = 0;
}
int main() {
	freopen ("game.in", "r", stdin);
	freopen ("game.out", "w", stdout);
	for (int i=1; i<L; i++)
		pc[i] = pc[i>>1] ^ (i & 1);
	n = read();
	for (int i=1; i<=n; i++)
		c[i] = read() & 1;
	for (int i=P2[0]=1; i<n; i++)
		u = read(), v = read(), adj[u] += v, adj[v] += u, P2[i] = R(P2[i-1], P2[i-1]);
	dfs(1, 0);
	for (int i=0; i<=mx[1]; i++)
		for (int j=0; j<L; j++)
			ans = R(ans, f[1][i]. a[j]);
	cout << (P2[n-1] + 31195136ll * ans) % MOD;
}