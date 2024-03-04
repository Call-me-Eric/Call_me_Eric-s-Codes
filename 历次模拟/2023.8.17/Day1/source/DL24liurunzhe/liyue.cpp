# include <cstdio>
# include <vector>
# include <ctime>
# include <cctype>
# include <cassert>
# include <iostream>
# include <algorithm>

# define TIME (clock() * 1.0 / CLOCKS_PER_SEC)

using std::min;

const int MAXN = 1e5 + 5;
const int len = 14;

int n, m;

int a[MAXN], b[MAXN];

int vec[MAXN][320], cnt[MAXN];

int f[MAXN / len + 5][MAXN / len + 5];

int bel[MAXN << 1], L[MAXN << 1], R[MAXN << 1];

inline int Get(const int& x, const int& l, const int& r) {
	if (l > r) return 0;
	return std::upper_bound(vec[x] + 1, vec[x] + cnt[x] + 1, r) - std::upper_bound(vec[x] + 1, vec[x] + cnt[x] + 1, l - 1);
};

# define getchar() (std::cin.get())

inline int read() {
	int x = 0;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar());
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch - '0');
	return x;
}

int main() {
	
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
	
	n = read();
	for (int i = 1; i <= n; ++i) bel[i] = (i - 1) / len + 1;
	for (int i = 1; i <= bel[n]; ++i) 
		L[i] = R[i - 1] + 1, R[i] = min(n, L[i] + len - 1);
		
	for (int i = 1; i <= n; ++i) a[i] = read(), b[ a[i] ] = i;
	for (int i = 1; i <= n; ++i) {
		for (int sq = 1; sq * sq < 2 * n && sq * sq - a[i] <= n; ++sq) {
			if (sq * sq <= a[i]) continue;
			int j = b[ sq * sq - a[i] ];
			if (i == j) continue;
			if (bel[i] <= bel[j]) ++f[ bel[i] ][ bel[j] ];
			vec[j][ ++cnt[j] ] = i;
		}
	}
	for (int i = 1; i <= bel[n]; ++i) f[i][i] >>= 1;
	for (int k = 2; k <= bel[n]; ++k) {
		for (int l = 1; l + k - 1 <= bel[n]; ++l) {
			int r = l + k - 1;
			f[l][r] += f[l + 1][r] + f[l][r - 1] - f[l + 1][r - 1];
		}
	}
	m = read();
	for (int Q = 1; Q <= m; ++Q) {
		int l, r;
		l = read(), r = read();
		int ans = 0;
		if (bel[l] == bel[r]) {
			for (int i = l; i <= r; ++i)
				ans += Get(i, i + 1, r);
			
			std::cout << ans << '\n'; continue;
		}
		for (int i = l; i <= R[ bel[l] ]; ++i)
			ans += Get(i, i + 1, r);
		
		for (int i = L[ bel[r] ]; i <= r; ++i)
			ans += Get(i, R[ bel[l] ] + 1, i - 1);
		
		std::cout << ans + f[ bel[l] + 1 ][ bel[r] - 1 ] << '\n';
	}
	
	return 0;
}
