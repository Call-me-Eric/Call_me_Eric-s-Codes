#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 6;
int cas, n, u, v, w, edgenum, Head[N], Next[N<<1], vet[N<<1], val[N<<1], top[N]; ll siz[N], ans;
char buf[1<<22], * S, * T;
#define gc ch = (T == S ? T = (S = buf) + fread(buf, 1, 1 << 22, stdin) : 0, T == S ? EOF : * S ++)
int read() {
	int s = 0; char gc;
	while (ch < '0' || ch > '9') gc;
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', gc;
	return s;
}
void add(int u, int v, int w) {
	Next[++edgenum] = Head[u];
	Head[u] = edgenum;
	vet[edgenum] = v;
	val[edgenum] = w;
}
void dfs1(int u, int fa, int t) {
	top[u] = t;
	for (int e=Head[u]; e; e=Next[e]) {
		int v=vet[e], w=val[e];
		if (v ^ fa) dfs1(v, u, w > 1 ? t : v), siz[t] += w & - 2;
	}
}
ll dfs2(int u, int fa) {
	ll fm = 0, sm = 0;
	for (int e=Head[u]; e; e=Next[e]) {
		int v=vet[e];
		if (v ^ fa) {
			ll l = dfs2(v, u) + (val[e] & 1 ? 1 : - 1);
			if (l >= fm) sm = fm, fm = l;
			else sm = max(sm, l);
		}
	} ans = max(ans, fm + sm + siz[top[u]]);
	return fm + siz[u];
}
int main() {
	freopen ("plan.in", "r", stdin);
	freopen ("plan.out", "w", stdout);
	cas = read();
	while (cas --) {
		n = read(), edgenum = ans = 0;
		for (int i=1; i<=n; i++)
			Head[i] = siz[i] = 0;
		for (int i=1; i<n; i++)
			u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
		dfs1(1, 0, 1), dfs2(1, 0), printf ("%lld\n", ans);
	}
}
