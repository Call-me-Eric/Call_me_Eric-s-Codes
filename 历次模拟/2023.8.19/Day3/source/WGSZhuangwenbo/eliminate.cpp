#include <cstdio>
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

const int N = 1e6;
const int M = 2e6;
const int LOGM = 21;

int n; std::vector<int> a[N + 5];
int b[M + 5], bct; std::vector<int> buc[M + 5];

#define lch (p * 2)
#define rch (p * 2 + 1)
#define mid ((cl + cr) / 2)
int mn[M * 4 + 5];
void pushup(int p) { mn[p] = std::min(mn[lch], mn[rch]); }
void upd(int x, int d, int p = 1, int cl = 1, int cr = n) {
	if(cl == cr) return mn[p] += d, void();
	(x <= mid) ? upd(x, d, lch, cl, mid) : upd(x, d, rch, mid + 1, cr);
	pushup(p);
}
#undef lch
#undef rch
#undef mid

int main() {
	freopen("eliminate.in", "r", stdin), freopen("eliminate.out", "w", stdout);

	n = rd();
	for(int i = 1; i <= n; i++) {
		int c = rd(); a[i].resize(c);
		for(int j = 0; j < c; j++) {
			a[i][j] = b[++bct] = rd();
		}
	}
	std::sort(b + 1, b + 1 + bct), bct = std::unique(b + 1, b + 1 + bct) - b - 1;

	for(int i = 1; i <= n; i++) {
		for(int v : a[i]) {
			int nv = std::lower_bound(b + 1, b + 1 + bct, v) - b;
			buc[nv].push_back(i);
		}
	}

	int ans = 2e9;
	for(int i = 1, j = 0; i <= bct; i++) {
		for(int pos : buc[i]) upd(pos, 1);
		while(j <= bct && mn[1]) {
			for(int pos : buc[j]) upd(pos, -1);
			j++;
		}
//		assert(j <= i + 1);
		if(j) ans = std::min(ans, b[i] - b[j - 1]);
	}
	printf("%d\n", ans);
	return 0;
}

