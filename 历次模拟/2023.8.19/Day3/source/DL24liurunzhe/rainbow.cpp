# include <cstdio>
# include <cctype>
# include <utility>
# include <cassert>
# include <algorithm>

class IO {
	static constexpr int MAXS = 1 << 20;
	
	char buf[MAXS], *p1 = buf, *p2 = buf;
	
	# define GetC() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXS, stdin), p1 == p2) ? EOF : *p1 ++)
	
 public:
	template <typename T> inline void read(T& x) {
		x = 0; char ch = GetC();
		for (; !isdigit(ch); ch = GetC());
		for (; isdigit(ch); ch = GetC()) x = x * 10 + ch - '0';
	}
	
	template <typename T, typename ...Args> inline void read(T& x, Args& ...rest) {
		read(x), read(rest...);
	}
} io;

using std::min;

typedef std::pair<int, int> Pii;

constexpr int MAXN = 2e3 + 5;

int n, m;

int r[MAXN][MAXN], c[MAXN][MAXN];
int a[MAXN][MAXN], siz[MAXN][MAXN], sum[MAXN][MAXN];

Pii arr[MAXN << 2];

int vis[MAXN * MAXN], lenl[MAXN][MAXN], lenr[MAXN][MAXN];

int main() {
	
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	
	io.read(n, m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			io.read(a[i][j]), lenl[i][j] = lenr[i][j] = n + m;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!a[i - 1][j - 1] || a[i][j] == a[i - 1][j - 1]) 
				r[i][j] = r[i][j - 1] + 1, c[i][j] = c[i - 1][j] + 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		int num = 0;
		for (int x = i, y = 1; x >= 1 && y <= m; --x, ++y) {
			arr[++num] = Pii(x, y);
		}
		for (int j = 1; j <= num; ++j) {
			int x = arr[j].first, y = arr[j].second;
			if (vis[ a[x][y] ]) {
				int len = j - vis[ a[x][y] ];
				lenl[x][y] = lenr[ arr[ vis[ a[x][y] ] ].first ][ arr[ vis[ a[x][y] ] ].second ] = len;
			}
			vis[ a[x][y] ] = j;
		}
		for (int j = 1; j <= num; ++j) {
			vis[ a[ arr[j].first ][ arr[j].second ] ] = 0;
		}
	}
	for (int i = 2; i <= m; ++i) {
		int num = 0;
		for (int x = n, y = i; x >= 1 && y <= m; --x, ++y) {
			arr[++num] = Pii(x, y);
		}
		for (int j = 1; j <= num; ++j) {
			int x = arr[j].first, y = arr[j].second;
			if (vis[ a[x][y] ]) {
				int len = j - vis[ a[x][y] ];
				lenl[x][y] = lenr[ arr[ vis[ a[x][y] ] ].first ][ arr[ vis[ a[x][y] ] ].second ] = len;
			}
			vis[ a[x][y] ] = j;
		}
		for (int j = 1; j <= num; ++j) {
			vis[ a[ arr[j].first ][ arr[j].second ] ] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			siz[i][j] = min({ siz[i - 1][j - 1], c[i][j], r[i][j] });
			if (lenr[ i - siz[i][j] ][j] > siz[i][j] && lenl[i][ j - siz[i][j] ] > siz[i][j]) ++siz[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) 
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] + siz[i][j] - sum[i - 1][j - 1];;
	}
	printf("%d\n", sum[n][m]);
	
	return 0;
}
