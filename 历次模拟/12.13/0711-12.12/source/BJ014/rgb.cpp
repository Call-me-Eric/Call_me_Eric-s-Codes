#include <bits/stdc++.h>
using namespace std;

const int N = 255, M = 0x1f1e33;
typedef unsigned long long ull;

int n, m, u[M], v[M], lim[3], c[M], cnt[3], f[N], tfa[N], dep[N], tfe[N];
bool ans[M];
ull hsv[N][3];
vector <int> g[3];
set <int> adj[N];

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

inline void Init() {
	for (int i = 1;i <= n;i++) f[i] = i;
}

inline int GetRoot(int v) {
	if (f[v] == v) return v;
	return f[v] = GetRoot(f[v]);
}

inline bool Merge(int x, int y) {
	int u = GetRoot(x), v = GetRoot(y);
	if (u != v) f[v] = u;
	return u != v;
}

inline void Read() {
	cin >> lim[0] >> lim[1] >> lim[2] >> m;
	n = lim[0] + lim[1] + lim[2] + 1;
	for (int i = 1;i <= m;i++) {
		char col;
		cin >> u[i] >> v[i] >> col;
		if (col == 'r') g[c[i] = 0].push_back(i);
		if (col == 'g') g[c[i] = 1].push_back(i);
		if (col == 'b') g[c[i] = 2].push_back(i);
	}
}

inline void Prefix() {
	Init();
	for (int i = 1;i <= m;i++) {
		if (Merge(u[i], v[i])) {
			adj[u[i]].insert(i);
			adj[v[i]].insert(i);
			cnt[c[i]]++;
			//cout << u[i] << "<->" << v[i] << endl;
		}
	}
}

inline void Dfs(int x, int fa) {
	for (int e : adj[x]) {
		int y = x ^ u[e] ^ v[e];
		if (y != fa) {
			for (int i = 0;i < 3;i++) {
				if (i != c[e]) hsv[y][i] = hsv[x][i];
				else hsv[y][i] = hsv[x][i] ^ rnd();
			}
			tfa[y] = x;
			tfe[y] = e;
			Dfs(y, x);
		}
	}
}

inline bool chkFail() {
	for (int i = 0;i < 3;i++) {
		Init();
		int cnt = 0;
		for (int j = 1;j <= m;j++) {
			if (c[j] == i) {
				cnt += Merge(u[j], v[j]);
			}
		}
		if (cnt < lim[i]) return 1;
		Init(); cnt = 0;
		for (int j = 1;j <= m;j++) {
			if (c[j] != i) {
				cnt += Merge(u[j], v[j]);
			}
		}
		if (cnt < n - lim[i] - 1) return 1;
	}
	return 0;
}

inline void Solve() {
	if (chkFail()) {
		cout << "NO" << endl;
		return;
	}
	//cout << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
	while (cnt[0] != lim[0] || cnt[1] != lim[1] || cnt[2] != lim[2]) {
		int mic = 0;
		int idx = -1, adc = -1;
		for (mic = 0;mic < 3;mic++) {
			if (lim[mic] > cnt[mic]) {
				tfa[1] = -1; tfe[1] = -1;
				Dfs(1, -1);
				for (int i : g[mic]) {
					for (int j = 0;j < 3;j++) {
						if (cnt[j] > lim[j] && (hsv[u[i]][j] ^ hsv[v[i]][j]) != 0) {
							idx = i;
							adc = j;
							goto done;
						}
					}
				}
				for (int i : g[mic]) {
					for (int j = 0;j < 3;j++) {
						if (cnt[j] == lim[j] && (hsv[u[i]][j] ^ hsv[v[i]][j]) != 0) {
							idx = i;
							adc = j;
							goto done;
						}
					}
				}
			}
		}
		
		//assert(0);
		done:;
		tfa[u[idx]] = -1;
		tfe[u[idx]] = -1;
		Dfs(u[idx], -1);
		int t = v[idx], ade = -1;
		while (t != u[idx]) {
			if (c[tfe[t]] == adc) {
				ade = tfe[t];
				break;
			}
			t = tfa[t];
		}
		//assert(ade != -1);
		cnt[c[ade]]--;
		cnt[c[idx]]++;
		adj[u[ade]].erase(ade);
		adj[v[ade]].erase(ade);
		adj[u[idx]].insert(idx);
		adj[v[idx]].insert(idx);
	}
	cout << "YES\n";
	for (int i = 1;i <= m;i++) ans[i] = 0;
	for (int i = 1;i <= n;i++) {
		for (int e : adj[i]) ans[e] = 1;
	}
	for (int i = 1;i <= m;i++) cout << ans[i];
	cout << endl;
}

int main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Read();
	Prefix();
	Solve();
	return 0;
}
