#include <iostream>
#include <map>
using namespace std;
constexpr int MAXN(1000007);
constexpr int mod(998244353);
inline void read(int &temp) { cin >> temp; }
map <int, pair<int, int> > fdpos;
map <pair<int, int>, int> fdnum;
int xx[] = {1, 0, -1, 0};
int yy[] = {0, 1, 0, -1};
int a[MAXN];
int n, x, y, stp, lmt, jl, fx, m, tp;
int main() {
	freopen("maze.in", "r", stdin);
	freopen("maze.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(m), read(tp);
	lmt = 1, n = 100000;
	fdnum[make_pair(0, 0)] = 1, fdpos[1] = make_pair(0, 0);
	for (int i(2); i <= n; ++i) {
		x += xx[fx], y += yy[fx];
		fdnum[make_pair(x, y)] = i, fdpos[i] = make_pair(x, y);
		++stp;
		if (stp == lmt)  ++jl, stp = 0, fx = (fx + 1) % 4;
		if (jl == 2)  jl = 0, ++lmt;
	}
	for (int i(1), opt, u, v, w; i <= m; ++i) {
		read(opt), read(u), read(v);
		if (opt == 1) {
			read(w);
			for (int i(u); i <= v; ++i)  a[i] = (a[i] + w > mod) ? (a[i] + w - mod) : (a[i] + w);
		}
		if (opt == 2) {
			int tx = fdpos[u].first, ty = fdpos[u].second;
			for (int i = min(tx, 0); i <= max(tx, 0); ++i) 
				for (int j = min(ty, 0); j <= max(ty, 0); ++j)  a[fdnum[make_pair(i, j)]] = (a[fdnum[make_pair(i, j)]] + v) % mod;
		}
		if (opt == 3) {
			int res(0);
			for (int i(u); i <= v; ++i)  res = (res + a[i] > mod) ? (res + a[i] - mod) : (res + a[i]);
			cout << res << '\n';
		}
	}
	return 0;
}
