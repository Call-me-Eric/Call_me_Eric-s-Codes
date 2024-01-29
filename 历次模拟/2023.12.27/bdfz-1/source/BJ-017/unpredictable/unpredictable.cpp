#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1e6 + 5;
const ull base = 131;
const int P = 998244353;

int n, m = 1e6;
int son[N][26], tt = 1;
int ans, res;
ull pw[N];
string str[N];
vector<ull> hs[N], hss;
vector<int> a[N], adj[N], bdj[N];
int cur[N];
int sti[N], stj[N], top;
int cnt = 0;

void ins(string s, int id) {
	reverse(s.begin(), s.end());
	int o = 1;
	for(char ch : s) {
		if(!son[o][ch-'a']) son[o][ch-'a'] = ++tt;
		o = son[o][ch-'a'];
	}
	bdj[o].pb(id);
}

inline void dfs(int o, ull hs, int d) {
	int t0 = top;
	auto it = lower_bound(hss.begin(), hss.end(), hs);
	if(it != hss.end() && *it == hs) {
		int p = it - hss.begin() + 1;
		for(int i : adj[p]) {
			++cnt;
			++top;
			sti[top] = i;
			res = (res - (stj[top] = cur[i])) % P;
			res = (res + (cur[i] = a[i][d])) % P;
		}
	}
	for(int i : bdj[o]) {
		++cnt;
		ans = (ans + res) % P;
		ans = (ans - a[i][str[i].size()]) % P;
	}
	rep(i, 0, 25) if(son[o][i]) {
		dfs(son[o][i], hs + pw[d] * ('a' + i), d+1);
	}
	while(top > t0) {
		res = (res - cur[sti[top]]) % P;
		res = (res + (cur[sti[top]] = stj[top])) % P;
		--top;
	}
}

void solve() {
	hss.clear();
	rep(i, 1, m) adj[i].clear(), bdj[i].clear();
	memset(son, 0, sizeof son);
	tt = 1;

	rep(i, 1, n) {
		int k = str[i].size();
		rep(j, 1, k) hs[i][j] = hs[i][j-1] * base + str[i][j-1], hss.pb(hs[i][j]);
	}
	sort(hss.begin(), hss.end());
	hss.erase(unique(hss.begin(), hss.end()), hss.end());
	rep(i, 1, n) {
		int k = str[i].size();
		rep(j, 1, k) {
			int p = lower_bound(hss.begin(), hss.end(), hs[i][j]) - hss.begin() + 1;
			adj[p].pb(i);
		}
	}
	rep(i, 1, n) ins(str[i], i);
	dfs(1, 0, 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	freopen("unpredictable.in", "r", stdin);
	freopen("unpredictable.out", "w", stdout);


	pw[0] = 1;
	rep(i, 1, m) pw[i] = pw[i-1] * base;

	cin >> n;
	int sum = 0;
	rep(i, 1, n) {
		cin >> str[i];
		int k = str[i].size();
		sum += k;
		hs[i].resize(k+1);
		a[i].resize(k+1);
		rep(j, 1, k) cin >> a[i][j];
	}
	solve();
	rep(i, 1, n) reverse(str[i].begin(), str[i].end());
	solve();
	rep(i, 1, n-1) ans = 1ll * ans * i % P;
	cout << (ans + P) % P << "\n";

	return 0;
}

