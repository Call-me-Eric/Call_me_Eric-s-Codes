#include <bits/stdc++.h>
#define p0 putchar('0')
#define p1 putchar('1')
using namespace std;

const int N = 1e6 + 10;
int n, k, cnt, pr[N], Min[N]; bool isp[N];
int cur, op[N], arr[N], seq[N], chose[N];

inline void init() {
	for (int i = 2; i <= 1e6; ++i) {
		if (!Min[i]) isp[pr[++cnt] = Min[i] = i] = true;
		for (int j = 1; j <= cnt && i * pr[j] <= 1e6; ++j) {
			if (pr[j] > Min[i]) break;
			Min[i * pr[j]] = pr[j];
		}
	}
}

inline void solve1() {
	for (int i = 1; i <= n; ++i) p1;
} inline void solve2() {
	for (int i = 1; i <= k; ++i) p1;
	for (int i = k + 1; i <= n; ++i) p0;
} inline void solve3() {
	int len = 0, siz = 0;
	for (int i = 2; i <= n / 2; ++i) {
		if (n % i == 0)
			for (int j = 1; j <= n / i; ++j)
				chose[++siz] = i;
	}
	int num = 0;
	for (int sta = 1; sta < (1 << siz); ++sta) {
		int gap = 0, tmp = 0;
		for (int i = 1; i <= siz; ++i)
			if (sta >> (i - 1) & 1) { gap = chose[i]; break; }
		int tot = __builtin_popcount(sta);
		if (tot > gap) continue;
		for (int i = 1; i <= siz; ++i)
			if (sta >> (i - 1) & 1) op[++tmp] = chose[i];
		for (int i = 1; i <= gap; ++i) arr[i] = i;
		do {
			bool ok = true; bool vis[n + 5] = {false};
			for (int i = 1; i <= tot; ++i) {
				int curp = arr[i];
				for (int j = 1; j <= n / op[i]; ++j) {
					if (vis[curp]) { ok = false; break; }
					vis[curp] = true, curp += op[i];
					if (curp > n) curp -= n;
				}
				if (!ok) break;
			}
			if (!ok) continue; int all = 0;
			for (int i = 1; i <= n; ++i) all += vis[i];
			if (all > k) continue;
			if (all > num) {
				num = all;
				for (int i = 1; i <= n; ++i) seq[i] = vis[i];
			}
		} while (next_permutation(arr + 1, arr + 1 + gap));
	}
	for (int i = 1; i <= n; ++i) seq[i]? p1 : p0;
} inline void solve5() {
	for (int i = 1; i <= n; ++i) p0;
}

int main() {
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	scanf("%d%d", &n, &k), init();
	if (k == n) return solve1(), 0; // Subtask1, 1pts
	if (k <= 1) return solve2(), 0; // Subtask2, 1pts
	if (isp[n]) return solve5(), 0; // Subtask5, 2pts
	return solve3(), 0; // Subtask3, 5pts -> ?
}
