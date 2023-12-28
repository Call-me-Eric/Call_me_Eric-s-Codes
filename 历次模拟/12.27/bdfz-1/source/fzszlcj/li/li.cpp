#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using vi = vector<int>;
using pii = pair<int, int>;
#define pb emplace_back
#define sz(a) int(a.size())

const int N = 2e5;
int n, m, fa[N + 5], sz[N + 5], ec[N + 5], degmx[N + 5], deg[N + 5];

int getf(int x)
{
	return x == fa[x] ? x : fa[x] = getf(fa[x]);
}

int ans1;
LL ans0;
bool circle = false;

signed main()
{
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
		ec[i] = 0;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		++deg[u];
		++deg[v];
		u = getf(u);
		v = getf(v);
		if (u != v) {
			sz[u] += sz[v];
			ec[u] += ec[v];
			fa[v] = u;
		}
		++ec[u];
	}
	for (int i = 1; i <= n; ++i) {
		degmx[getf(i)] = max(degmx[getf(i)], deg[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (i == getf(i)) {
			if (ec[i] > sz[i]) {
				cout << -1;
				return 0;
			}
			if (ec[i] == sz[i]) {
				if (degmx[i] > 2) {
					cout << -1;
					return 0;
				}
				circle = true;
				ans1 += sz[i];
			}else {
				assert(ec[i] == sz[i] - 1);
				if (degmx[i] > 3) {
					cout << -1;
					return 0;
				}
				if (degmx[i] == 3) {
					if (sz[i] != 4) {
						cout << -1;
						return 0;
					}
					circle = true;
					ans1 += 3;
				}else {
					assert(degmx[i] <= 2);
					ans0 += 1ll * sz[i] * (sz[i] + 1) / 2;
				}
			}
		}
	}
	if (circle) {
		cout << 1 << ' ' << ans1 << '\n';
	}else {
		cout << 0 << ' ' << ans0 << '\n';
	}
	return 0;
}

