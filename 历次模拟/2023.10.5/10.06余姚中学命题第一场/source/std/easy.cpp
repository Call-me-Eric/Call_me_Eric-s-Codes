#include <bits/stdc++.h>
using namespace std;
const int Q = 5e5 + 5, N = Q << 3, A = 1e7, MOD = 998244353;
int I[A+5], c, p[A+5], f[A+5], q, a, s, now[A+5], nodes, head[A+5], tail[A+5], nxt[N], val[N], tim[N], ans[Q], dl[Q], dr[Q], c0[Q], cnt[Q], Ic[Q], prod = 1; bitset <A+5> np;
int read() {
	int s = 0, w = 1; char ch = getchar();
	while (ch < '0' || ch > '9') ch == '-' ? w = - w : 0, ch = getchar();
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int sgn(int x) { return (x > 0) - (x < 0); }
int qpow(int x, int y) { int t = 1; for (; y; y>>=1) y & 1 ? t = 1ll * t * x % MOD : 0, x = 1ll * x * x % MOD; return t; }
void add(int u, int v, int w) { (! head[u] ? head[u] : nxt[tail[u]]) = ++ nodes, tail[u] = nodes, val[nodes] = v, tim[nodes] = w; }
int main() {
	freopen ("easy.in", "r", stdin);
	freopen ("easy.out", "w", stdout);
	I[1] = ans[0] = dl[0] = 1;
	for (int i=2; i<=A; i++) {
		I[i] = 1ll * (MOD - MOD / i) * I[MOD%i] % MOD;
		if (! np[i]) p[++c] = i, f[i] = i;
		for (int j=1; j<=c && i*p[j]<=A; j++) {
			np[i*p[j]] = 1, f[i*p[j]] = p[j];
			if (! (i % p[j])) break;
		}
	}
	q = read();
	for (int i=1; i<=q; i++) {
		a = read(), s = sgn(a), a = abs(a);
		if (s > 0) now[a] ++;
		if (now[a] == 1) {
			int p = a - 1, l = f[p], c = 0;
			while (p > 1) {
				if (f[p] ^ l) add(l, c * s, i), l = f[p], c = 0;
				c ++, p /= l;
			} if (c) add(l, c * s, i);
			ans[i] = 1ll * ans[i-1] * (s > 0 ? a-1 : I[a-1]) % MOD;
		} else {
			add(a, (now[a] - 1 - (a == 2 && now[a] >= 3)) * s, i);
			ans[i] = 1ll * ans[i-1] * (s > 0 ? a : I[a]) % MOD;
		}
		if (s < 0) now[a] --;
		dl[i] = dr[i] = 1;
	} Ic[0] = cnt[0] = 1;
	for (int _=1; _<=c; _++) {
		int p = :: p[_], mx = 0, cm = 0;
		for (int e=head[p]; e; e=nxt[e]) {
			cnt[abs(val[e])] += sgn(val[e]);
			if (val[e] > 0) mx = max(mx, val[e]);
			else while (! cnt[mx]) mx --;
			if (! mx) continue;
			while (cm < cnt[mx]) cm ++, Ic[cm] = 1ll * Ic[cm-1] * I[p] % MOD;
			if (Ic[cnt[mx]] ^ 1)
				dl[tim[e]] = 1ll * dl[tim[e]] * (MOD + 1 - Ic[cnt[mx]]) % MOD, 
				dr[tim[nxt[e]]] = 1ll * dr[tim[nxt[e]]] * (MOD + 1 - Ic[cnt[mx]]) % MOD;
			else c0[tim[e]] ++, c0[tim[nxt[e]]] --;
		}
		while (mx) cnt[mx--] = 0;
	}
	for (int i=1; i<=q; i++) {
		dl[i] = 1ll * dl[i-1] * dl[i] % MOD, ans[i] = 1ll * ans[i] * dl[i] % MOD, prod = 1ll * prod * dr[i] % MOD;
		if (c0[i] += c0[i-1]) ans[i] = 0;
	}
	prod = qpow(prod, MOD - 2);
	for (int i=q; i; i--)
		ans[i] = 1ll * ans[i] * prod % MOD, prod = 1ll * prod * dr[i] % MOD;
	for (int i=1; i<=q; i++)
		write(ans[i]), putchar('\n');
}
