#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 255;
const int M = N * N;

int n, m, a, b, c;
int ans[M], ans0[M];
int eu[M], ev[M], ew[M];
int uni[M], sel[M];

inline int find(int x) {
	return x == uni[x] ? x : uni[x] = find(uni[x]);
}

void mst(int base) {
	rep(i, 1, m) sel[i] = 0;
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) if(ans[i] == 1) {
		int u = eu[i], v = ev[i];
		if(find(u) != find(v)) uni[find(u)] = find(v);
	}
	rep(i, 1, m) if(base >> ew[i] & 1) {
		int u = eu[i], v = ev[i];
		if(find(u) != find(v)) uni[find(u)] = find(v), sel[i] = 1;
	}
	rep(i, 1, m) if(!(base >> ew[i] & 1)) {
		int u = eu[i], v = ev[i];
		if(find(u) != find(v)) uni[find(u)] = find(v), sel[i] = 2;
	}
}

bool check() {
	int cnt = 0;
	mst(0b011);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 2;
	if(cnt > c) return 0;
	rep(i, 1, m) ans[i] |= sel[i] == 2;
	c -= cnt;
	mst(0b101);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 2;
	if(cnt > b) return 0;
	rep(i, 1, m) ans[i] |= sel[i] == 2;
	b -= cnt;
	mst(0b110);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 2;
	if(cnt > a) return 0;
	rep(i, 1, m) ans[i] |= sel[i] == 2;
	a -= cnt;

	mst(0b100);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 1;
	if(cnt < c) return 0;

	mst(0b010);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 1;
	if(cnt < b) return 0;

	mst(0b001);
	cnt = 0;
	rep(i, 1, m) cnt += sel[i] == 1;
	if(cnt < a) return 0;

	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);

	cin >> a >> b >> c >> m;
	n = a + b + c + 1;
	rep(i, 1, m) {
		char ch;
		cin >> eu[i] >> ev[i] >> ch;
		if(ch == 'r') ew[i] = 0;
		else if(ch == 'g') ew[i] = 1;
		else ew[i] = 2;
	}
	if(!check()) {
		cout << "NO" << "\n";
		return 0;
	}

	while(a + b + c) {
		rep(i, 1, n) uni[i] = i;
		rep(i, 1, m) if(ans[i] == 1) uni[find(eu[i])] = find(ev[i]);
		vector<int> v;
		if(a) rep(i, 1, m) if(ew[i] == 0 && find(eu[i]) != find(ev[i]) && !ans[i]) {
			v.pb(i);
			break;
		}
		if(b) rep(i, 1, m) if(ew[i] == 1 && find(eu[i]) != find(ev[i]) && !ans[i]) {
			v.pb(i);
			break;
		}
		if(c) rep(i, 1, m) if(ew[i] == 2 && find(eu[i]) != find(ev[i]) && !ans[i]) {
			v.pb(i);
			break;
		}
		bool ok = 0;
		for(int e : v) {
			memcpy(ans0, ans, sizeof ans0);
			int a0 = a, b0 = b, c0 = c;
			ans[e] = 1;
			if(ew[e] == 0) --a;
			else if(ew[e] == 1) --b;
			else --c;
			if(check()) {
				ok = 1;
				break;
			}
			memcpy(ans, ans0, sizeof ans0);
			a = a0, b = b0, c = c0;
		}
		assert(ok);
	}

	cout << "YES" << "\n";
	rep(i, 1, m) cout << ans[i];
	cout << "\n";

	return 0;
}
