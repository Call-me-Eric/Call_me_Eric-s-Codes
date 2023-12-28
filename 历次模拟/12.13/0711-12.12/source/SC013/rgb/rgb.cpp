#include <bits/stdc++.h>

using namespace std;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

inline char readchar() {
	register char ch = getchar();
	while (!isalpha(ch)) ch = getchar();
	return ch;
}

const int N = 1e5 + 5;

struct edge {
	int from, to, c, id;
} ed[N];

int r, g, b, n, m, f[N], T, top = 0, t = 0;
int id[205], cnt[205];
int res[N];

mt19937 rnd(1992608117);

inline int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

inline bool calc() {
	mt19937 sf(rnd());
	for (int i = 1; i <= n; ++i) f[i] = i;
	shuffle(ed + 1, ed + top + 1, sf);
	cnt['r'] = r; cnt['g'] = g; cnt['b'] = b;
	for (int i = 1; i <= top; ++i) {
		if (!cnt[ed[i].c]) continue;
		int x = find(ed[i].from), y = find(ed[i].to);
		if (x == y) continue;
		res[ed[i].id] = t; --cnt[ed[i].c];
		f[x] = y;
	}
	if (cnt['r'] && id['r'] != 1) return 0;
	if (cnt['g'] && id['g'] != 1) return 0;
	if (cnt['b'] && id['b'] != 1) return 0;
	for (int i = top + 1; i <= m; ++i) {
		if (!cnt[ed[i].c]) break;
		int x = find(ed[i].from), y = find(ed[i].to);
		if (x == y) continue;
		res[ed[i].id] = t; --cnt[ed[i].c];
		f[x] = y;
	}
	if (cnt[ed[m].c]) return 0;
	puts("YES");
	for (int i = 1; i <= m; ++i) putchar(48 ^ (res[i] == t));
	return 1;
}

int main() {
	freopen("rgb.in", "r", stdin); freopen("rgb.out", "w", stdout);
	r = read(); g = read(); b = read(); m = read(); n = r + g + b + 1;
	id['r'] = 1; id['g'] = 2; id['b'] = 3;
	for (int i = 1; i <= m; ++i) {
		ed[i].from = read(); ed[i].to = read();
		ed[i].c = readchar(); ++cnt[ed[i].c];
		ed[i].id = i;
	}
	if (cnt['r'] < r || cnt['g'] < g || cnt['b'] < b) {
		puts("NO"); return 0;
	}
	if (r > g) swap(id['r'], id['g']);
	if (r > b) swap(id['r'], id['b']);
	if (g > b) swap(id['g'], id['b']);
	for (int i = 1; i <= m; ++i)
		if (id[ed[i].c] != 1) swap(ed[i], ed[++top]);
	int T = 25000000 / m;
	while (T--) {
		++t;
		if (calc()) return 0;
	} puts("NO");
	return 0;
}
