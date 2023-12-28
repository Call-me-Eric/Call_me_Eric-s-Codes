#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1e6 + 5;
const int M = 3e5 + 5;
const int BL = sqrt(M);
const int A = 134775813;
const int B = 1103515245;
const int C = 1013904223;

int n = 1e6, q, P, T;
int a[N], b[N], c[N], tmp1[N], tmp2[N], pos;
ll ql[N], qr[N];
vector<pair<int, int>> adj[N];
vector<int> bdj[N];
int vis[N];
uint ans[N], res[N], rres[N];

void init() {
	a[1] = A % P;
	memset(vis, -1, sizeof vis);
	vis[a[1]] = 1;
	rep(i, 2, n) {
		a[i] = (1ll * B * a[i-1] + C) % P;
		if(!T && vis[a[i]] != -1) {
			T = i - vis[a[i]];
			pos = i;
		}
		vis[a[i]] = i;
	}
	assert(T + pos <= n);
	rep(i, 1, n) {
		if(a[i] % 2 == 1) b[i] = 4 - 3;
		else if(a[i] % 4 == 0) b[i] = 1 - 3;
		else b[i] = 3 - 3;
	}
	rep(i, 1, n) c[i] = c[i-1] + b[i];
}

ll calc(ll n) {
	return a[(n - pos) % T + pos];
}

/*
inline void cdq2(int l, int r, int ql, int qr) {
	if(l != r) {
		int mid = l + r >> 1;
		cdq2(l, mid, ql, qr);
		cdq2(mid+1, r, ql, qr);
		int i = l, j = mid+1;
		int k = l;
		while(i <= mid || j <= r) {
			if(i == mid+1 || (j <= r && c[i] >= c[j])) {
				tmp1[k++] = c[j++];
			} else {
				tmp1[k++] = c[i++];
			}
		}
		rep(i, l, r) c[i] = tmp[i];
	}
	rep(i, ql, qr) res[i] = 0;
	int i = l, j = ql;
	while(i <= r || j <= qr) {
		if(i == r+1 || (j <= qr && c[i] >= c[j])) {
			res[j++] += i-l;
		} else {
			++i;
		}
	}
	rep(i, ql, qr) rres[i] = res[p[i]];
	rep(i, ql+1, qr) rres[i] += rres[i-1];
	rep(i, ql, qr) for(auto e : adj[i]) {
		int j = e.fi, id = e.se;
		if(j <= l) ans[id] += res[i];
	}
}

inline void cdq1(int l, int r) {

}

void solve1() {
	n = 3e5;
	rep(i, 1, n) c[i] = c[i-1] + b[i];
	int mi = *min_element(c, c + n + 1);
	rep(i, 0, n) c[i] -= mi-1;
	rep(i, 1, q) adj[qr[i]].emplace_back(ql[i], i);
	cdq1(1, n);
}
*/

int t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= 2005; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

void solve2(int id) {
	ll l = ql[id], r = qr[id];
	uint ans = 0;
	b[0] = calc(l-1);
	ll n = r-l+1;
	assert(n <= 2000);
	rep(i, 1, n) b[i] = (1ll * B * b[i-1] + C) % P;
	rep(i, 1, n) {
		if(b[i] % 2 == 1) b[i] = 4 - 3;
		else if(b[i] % 4 == 0) b[i] = 1 - 3;
		else b[i] = 3 - 3;
	}
	rep(i, 1, n) b[i] += b[i-1];
	int mi = *min_element(b, b + n + 1);
	rep(i, 0, n) b[i] -= mi-1;
	rep(i, 0, n) t[i] = 0;
	rep(i, 1, n) {
		add(b[i-1], 1);
		ans += query(b[i]-1);
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	freopen("dark.in", "r", stdin);
	freopen("dark.out", "w", stdout);

	cin >> P >> q;
	rep(i, 1, q) cin >> ql[i] >> qr[i];

	init();
	rep(i, 1, q) solve2(i);

	/*
	if(*max_element(qr + 1, qr + q + 1) <= n) {
		solve1();
	} else {
		rep(i, 1, q) solve2(i);
	}
	*/

	return 0;
}

