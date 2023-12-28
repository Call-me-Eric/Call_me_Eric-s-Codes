#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 705;
const int P = 998244353;

ll qpow(ll x, ll p) {
	ll res = 1, base = x;
	while(p) {
		if(p & 1) res = res * base % P;
		base = base * base % P;
		p >>= 1;
	}
	return res;
}

int n, q;

namespace sub1 {
vector<ll> las[N];
int last[N];
vector<vector<ll>> adj[N<<2];
ll a[N][N], res[N];
bool bad, mult;

int ins(vector<ll> v) {
	rep(i, 0, n-1) if(v[i]) {
		if(!a[i][i]) {
			ll t = qpow(v[i], P-2);
			rep(j, i, n) a[i][j] = t * v[j] % P;
			rep(j, i, n) if(a[i][j] < 0) a[i][j] += P;
			return i;
		} else {
			ll t = v[i];
			rep(j, i, n) v[j] = (v[j] - t * a[i][j]) % P;
		}
	}
	return v[n] ? -1 : -2;
}

void add(int o, int ql, int qr, const vector<ll>& v, int l, int r) {
	if(ql <= l && r <= qr) {
		adj[o].push_back(v);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, v, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, v, mid+1, r);
}

void dfs(int o, int l, int r) {
	bool bad0 = bad, mult0 = mult;
	vector<int> pos;
	if(!bad) {
		for(const auto& v : adj[o]) {
			int p = ins(v);
			if(p == -1) {
				bad = 1;
				break;
			} else if(p == -2) {
				mult = 1;
			} else {
				pos.push_back(p);
			}
		}
	}
	if(l == r) {
		if(bad) cout << "No" << "\n";
		else if(mult) cout << "Many" << "\n";
		else {
			rep(i, 0, n-1) res[i] = a[i][n];
			per(i, 0, n-1) rep(j, 0, i-1) res[j] = (res[j] - a[j][i] * res[i]) % P;
			rep(i, 0, n-1) cout << (res[i] + P) % P << " \n"[i == n-1];
		}
	} else {
		int mid = l + r >> 1;
		dfs(o << 1, l, mid);
		dfs(o << 1 | 1, mid + 1, r);
	}
	bad = bad0, mult = mult0;
	for(int p : pos) memset(a[p], 0, sizeof a[p]);
}

void solve() {
	rep(i, 1, n) {
		las[i].resize(n+1);
		for(ll& x : las[i]) cin >> x;
	}
	rep(i, 1, q) {
		int j; cin >> j;
		add(1, last[j], i-1, las[j], 0, q);
		for(ll& x : las[j]) cin >> x;
		last[j] = i;
	}
	rep(i, 1, n) add(1, last[i], q, las[i], 0, q);
	dfs(1, 0, q);
}
}

namespace sub2 {
int a[N][N], b[N][N], c[N][N], d[N], e[N], pos[N], res[N];

void ins(int id) {
	memcpy(d, a[id], sizeof a[id]);
	memset(e, 0, sizeof e);
	cerr << "ins = "; rep(i, 1, n) cerr << d[i] << " \n"[i == n];
	e[id] = 1;
	rep(i, 1, n) {
		if(d[i]) {
			if(!c[i][i]) {
				int t = qpow(d[i], P-2);
				rep(j, 1, n) c[i][j] = d[j] = 1ll * t * d[j] % P;
				rep(j, 1, n) b[i][j] = e[j] = 1ll * t * e[j] % P;
				pos[id] = i;
				return;
			} else {
				int t = d[i];
				rep(j, 1, n) d[j] = (d[j] - 1ll * t * c[i][j]) % P;
				rep(j, 1, n) e[j] = (e[j] - 1ll * t * b[i][j]) % P;
				assert(d[i] == 0);
			}
		}
	}
}

void getans() {
	memset(res, 0, sizeof res);
	rep(i, 1, n) rep(j, 1, n) res[i] = (res[i] + 1ll * b[i][j] * a[j][n+1]) % P;
	per(i, 1, n) rep(j, 1, i-1) res[j] = (res[j] - 1ll * c[j][i] * res[i]) % P;
	rep(i, 1, n) cout << (res[i] + P) % P << " \n"[i == n];
}

void solve() {
	rep(i, 1, n) {
		rep(j, 1, n+1) cin >> a[i][j];
		ins(i);
	}
	getans();
	rep(i, 1, n) rep(j, 1, n) cerr << c[i][j] << " \n"[j ==n];
	while(q--) {
		int p; cin >> p;
		rep(i, 1, n+1) cin >> a[n+1][i];
		ins(n+1);
		int sum = 0;
		rep(i, 1, n) sum = (sum - 1ll * e[i] * a[i][n+1]) % P;
		cerr << "dsum = " << sum << "\n";
		int dt = 1ll * (a[n+1][n+1] - sum) % P;
		int t = qpow(e[p], P-2);
		a[p][n+1] = (a[p][n+1] + 1ll * dt * t) % P;
		rep(i, 1, n) cerr << -e[i] << " \n"[i == n];
		cerr << dt << " " << t << "\n";
		getans();
	}
}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);

	cin >> n >> q;
	sub1::solve();

	return 0;
}
