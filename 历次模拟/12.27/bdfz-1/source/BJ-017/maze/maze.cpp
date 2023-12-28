#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 2.1e5 + 5;
const int M = 3e7 + 5;
const int P = 998244353;

int n = 1e5, q, tp;
int sum[M], lazy[M], ls[M], rs[M], rt, tt;
int pos[N][4];
vector<pair<ll, int>> vec[4];

pair<int, int> getpos(ll v) {
	int p = sqrt(v);
	rep(i, p-1, p+2) if(1ll * i * i == v) {
		return i % 2 == 0 ? mp(-i/2+1, i/2) : mp(i/2, -i/2);
	}
	rep(i, p-1, p+2) if(1ll * i * i - 1 == v) {
		return i % 2 == 0 ? mp(-i/2+2, i/2) : mp(i/2-1, -i/2);
	}
	p = (1 + sqrt(1 + 4 * v)) / 2;
	rep(i, p-1, p+2) if(1ll * i * (i-1) == v) {
		return i % 2 == 0 ? mp(i/2, i/2-1) : mp(-i/2, -i/2+1);
	}
	assert(0);
}

int getp(int x, int y) {
	if(x >= 0 && y >= 0) {
		return max(x, y);
	} else if(x < 0 && y >= 0) {
		return max(-x, y);
	} else if(x < 0 && y < 0) {
		return max(-x, -y);
	} else {
		return max(x-1, -y);
	}
}

ll getval(pair<int, int> ps) {
	int x = ps.fi, y = ps.se;
	if(x == 0 && y == 0) return 1;
	if(x >= 0 && y >= 0) {
		int p = max(x, y);
		int d = x + p - y;
		return pos[p][0] - d;
	} else if(x < 0 && y >= 0) {
		int p = max(-x, y);
		int d = -x + p - y;
		return pos[p][0] + d;
	} else if(x < 0 && y < 0) {
		int p = max(-x, -y);
		int d = x + p - y;
		return pos[p][1] + d;
	} else {
		int p = max(x-1, -y);
		int d = x + y + p;
		return pos[p][2] + d;
	}
}

inline int newnode() {
	int o = ++tt;
	ls[o] = rs[o] = sum[o] = lazy[o] = 0;
	return o;
}

inline void setlazy(int& o, int x, ll l, ll r) {
	if(!o) o = newnode();
	sum[o] = (sum[o] + x * (r-l+1)) % P;
	lazy[o] = (lazy[o] + x) % P;
}

inline void pushdown(int o, ll l, ll r) {
	if(lazy[o]) {
		ll mid = l + r >> 1;
		setlazy(ls[o], lazy[o], l, mid);
		setlazy(rs[o], lazy[o], mid+1, r);
		lazy[o] = 0;
	}
}

inline void pushup(int o) {
	sum[o] = (sum[ls[o]] + sum[rs[o]]) % P;
}

inline void add(int& o, ll ql, ll qr, int x, ll l, ll r) {
	if(ql > qr) return;
	if(!o) o = newnode();
	if(ql <= l && r <= qr) return setlazy(o, x, l, r);
	pushdown(o, l, r);
	ll mid = l + r >> 1;
	if(ql <= mid) add(ls[o], ql, qr, x, l, mid);
	if(mid < qr) add(rs[o], ql, qr, x, mid+1, r);
	pushup(o);
}

inline int query(int o, ll ql, ll qr, ll l, ll r) {
	if(!o) return 0;
	if(!ls[o] && !rs[o]) return (min(qr, r) - max(ql, l) + 1) * lazy[o] % P;
	if(ql <= l && r <= qr) return sum[o];
	pushdown(o, l, r);
	ll mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res = (res + query(ls[o], ql, qr, l, mid)) % P;
	if(mid < qr) res = (res + query(rs[o], ql, qr, mid+1, r)) % P;
	return res;
}


int solve(ll m) {
	int res = query(rt, 1, m, 1, (ll)1e10);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	ll cur = 1;
	pos[0][0] = pos[0][1] = pos[0][2] = pos[0][3] = 1;
	rep(i, 1, n) {
		cur += 8 * i - 5;
		pos[i][0] = cur;
		pos[i][1] = cur + 2*i;
		pos[i][2] = cur + 4*i;
		pos[i][3] = cur + 6*i+1;
	}

	cin >> q >> tp;
	int las = 0;
	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			ll l, r; cin >> l >> r;
			int x; cin >> x;
			l ^= las, r ^= las, x ^= las;
			add(rt, l, r, x, 1, (ll)1e10);
		} else if(op == 2) {
			assert(0);
			ll v; cin >> v;
			int x; cin >> x;
			v ^= las, x ^= las;
			auto ps = getpos(v);
			if(ps.fi > 0 && ps.se >= 0) {
				add(rt, v-ps.se, v, x, 1, (ll)1e10);
				rep(i, 1, ps.se) add(rt, pos[i-1][3], pos[i][0], x, 1, (ll)1e10);
			} else if(ps.fi <= 0 && ps.se > 0) {
				add(rt, v+ps.fi, v, x, 1, (ll)1e10);
				rep(i, 0, -ps.fi-1) add(rt, pos[i][0], pos[i][1], x, 1, (ll)1e10);
			} else if(ps.fi <= 0 && ps.se <= 0) {
				add(rt, v+ps.se, v, x, 1, (ll)1e10);
				rep(i, 0, -ps.fi-1) add(rt, pos[i][1], pos[i][2], x, 1, (ll)1e10);
			} else {
				add(rt, v-ps.fi+1, v, x, 1, (ll)1e10);
				rep(i, 0, ps.fi-1) add(rt, pos[i][2], pos[i][3], x, 1, (ll)1e10);
			}
		} else {
			ll l, r; cin >> l >> r;
			l ^= las, r ^= las;
			int res = query(1, l, r, 1, (ll)1e10);
			cout << (las = res) << "\n";
		}
		if(!tp) las = 0;
	}

	return 0;
}

