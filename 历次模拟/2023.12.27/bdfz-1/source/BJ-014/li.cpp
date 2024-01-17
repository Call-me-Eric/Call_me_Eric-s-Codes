#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int dgr[N], n, m, u[N], v[N], f[N], sum[N], siz[N], mxd[N];

inline void Init() {
	for (int i = 1;i <= n;i++) {
		f[i] = i;
		siz[i] = 1;
		sum[i] = dgr[i];
		mxd[i] = dgr[i];
	}
}

inline int GetRoot(int v) {
	if (f[v] == v) return v;
	return f[v] = GetRoot(f[v]);
}

inline void Merge(int x, int y) {
	int u = GetRoot(x), v = GetRoot(y);
	if (u != v) {
		f[v] = u;
		siz[u] += siz[v];
		sum[u] += sum[v];
		mxd[u] = max(mxd[u], mxd[v]);
	}
}

inline void Read() {
	cin >> n >> m;
	for (int i = 1;i <= m;i++) {
		cin >> u[i] >> v[i];
		dgr[u[i]]++; dgr[v[i]]++;
	}
}

inline void Solve() {
	Init();
	for (int i = 1;i <= m;i++) Merge(u[i], v[i]);
	long long s = 0, k = 0;
	for (int i = 1;i <= n;i++) {
		if (GetRoot(i) == i) {
			if (mxd[i] <= 2) {
				if (siz[i] > sum[i] / 2) {
					if (s == 0) k += 1ll * siz[i] * (siz[i] + 1) / 2;
				} else {
					if (s == 0) {
						s = 1;
						k = 0;
					}
					k += siz[i];
				}
			} else if (mxd[i] == 3) {
				if (sum[i] >= 8 || siz[i] >= 5) {
					cout << "-1" << endl;
					return;
				} else {
					if (s == 0) {
						s = 1;
						k = 0;
					}
					k += 3;
				}
			} else {
				cout << "-1" << endl;
				return;
			}
		}
	}
	cout << s << " " << k << endl;
}

int main() {
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Read();
	Solve();
	return 0;
}
