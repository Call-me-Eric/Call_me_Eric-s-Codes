#include <cstdio>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using i64 = long long;

const int N = 3e3;

using u64 = unsigned long long;
const u64 B = 19260817;

char _b;

u64 pw[N + 5];
struct hsh {
	u64 h[N + 5];
	void set(int *a, int n) {
		for(int i = 1; i <= n; i++) h[i] = h[i - 1] * B + a[i];
	}
	u64 get(int l, int r) {
		return h[r] - h[l - 1] * pw[r - l + 1];
	}
} h1[N + 5], h2[N + 5];

int n, m, a[N + 5][N + 5];

i64 ans;
bool check(int x, int y, int mid) {
	return h1[x].get(y - mid + 1, y) == h1[x - 1].get((y - 1) - mid + 1, y - 1) && h2[y].get(x - mid + 1, x) == h2[y - 1].get((x - 1) - mid + 1, x - 1);
}
bool flg[N * N + 5];
void solve(int x, int y) {
	int len = 1; ans += len; x++, y++;
	flg[a[x][y]] = 1;
	for(; x <= n && y <= m; x++, y++) {
		int l = 1, r = len, res = 0;
		while(l <= r) {
			int mid = (l + r) / 2;
			if(check(x, y, mid)) l = mid + 1, res = mid;
			else r = mid - 1;
		}
		if(!res) {
			while(len) {
				flg[a[x - 1][(y - 1) - len + 1]] = 0;
				flg[a[(x - 1) - len + 1][y - 1]] = 0;
				len--;
			}
			flg[a[x][y]] = 1;
			len++;
		} else {
			while(len > res) {
				flg[a[x - 1][(y - 1) - len + 1]] = 0;
				flg[a[(x - 1) - len + 1][y - 1]] = 0;
				len--;
			}
			if(a[x][y - res] != a[x - res][y] && !flg[a[x][y - res]] && !flg[a[x - res][y]]) {
				flg[a[x][y - res]] = flg[a[x - res][y]] = 1;
				len++;
			}
		}
		ans += len;
	}
	while(len) {
		flg[a[x - 1][(y - 1) - len + 1]] = 0;
		flg[a[(x - 1) - len + 1][y - 1]] = 0;
		len--;
	}
}

char _e;

int main() {
//	debug("%lf MB\n", (&_e - &_b) / 1048576.);

	freopen("rainbow.in", "r", stdin), freopen("rainbow.out", "w", stdout);

	pw[0] = 1; for(int i = 1; i <= N; i++) pw[i] = pw[i - 1] * B;

	n = rd(), m = rd();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			a[i][j] = rd();
		}
	}
	static int t[N + 5];
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) t[j] = a[i][j];
		h1[i].set(t, m);
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) t[j] = a[j][i];
		h2[i].set(t, n);
	}

	for(int i = 1; i <= n; i++) solve(i, 1);
	for(int i = 2; i <= m; i++) solve(1, i);
	printf("%lld\n", ans);
	return 0;
}
/*
7 5
6 5 7 6 2
4 4 4 7 3
5 3 4 4 3
2 6 2 4 3
3 3 4 1 7
4 6 2 2 5
1 3 5 4 1

36
*/

