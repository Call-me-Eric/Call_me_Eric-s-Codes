#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9')
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

namespace steven24 {

const int N = 521;
const int mod = 998244353;

ll f[N][N][2];
int t[N][N];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int cnt, n, q;

struct node {
	int x, y, a;
	friend bool operator<(node x, node y) {
		return x.a < y.a;
	}
} a[N * N];

bool exist(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void solve(int fx, int fy) {
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) f[i][j][0] = f[i][j][1] = 0;
	for (int i = 1; i <= cnt; ++i) {
		int x = a[i].x, y = a[i].y;
		f[x][y][0] = 1;
//		if (x == fx && y == fy) {
//			f[x][y][0] = 0;
//			f[x][y][1] = 1;
//			continue;
//		}
		for (int j = 0; j < 4; ++j) {
			int tox = x + dx[j], toy = y + dy[j];
			if (!exist(tox, toy)) continue;
			if (tox == fx && toy == fy) continue;
			if (t[tox][toy] < t[x][y]) f[x][y][0] = (f[x][y][0] + f[tox][toy][0]) % mod;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
//			if (i == fx && j == fy) continue;
			for (int k = 0; k < 4; ++k) {
				int x = i + dx[k], y = j + dy[k];
				if (!exist(x, y)) continue;
				if (x == fx && y == fy) continue;
				if (t[x][y] >= t[i][j]) f[i][j][1] = (f[i][j][1] + f[x][y][0]) % mod;
			}
		}
	}
	
	ll ans = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) ans = (ans + f[i][j][0] + f[i][j][1]) % mod;
	printf("%lld\n", ans);
//	cout << f[fx][fy][0] << " " << f[fx][fy][1] << "\n";
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 1; j <= n; ++j) cout << f[i][j][0] << " " << f[i][j][1] << "  ";
//		cout << "\n";
//	}
}

void main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[++cnt].a = read();
			a[cnt].x = i;
			a[cnt].y = j;
			t[i][j] = a[cnt].a;
		}
	}
	q = read();
	sort(a + 1, a + 1 + cnt);
	while (q--) {
		int x = read(), y = read();
		solve(x, y);
	}
}

}

int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	steven24::main();
	return 0;
}
