#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 2e5 + 5;
const int P = 998244353;

string prm[] = {
"2", "3", "5", "7", "11", "19", "41", "61", "89", "409", "449", "499", "881", "991", "6469", "6949", "9001", "9049", "9649", "9949", "60649", "666649", "946669", "60000049", "66000049", "66600049"
};

int t;
map<vector<int>, int> mem;
vector<pair<int, int>> adj[N];
int f[105][N][2];
string l, r;

int dfs(vector<int> cur) {
	if(mem.count(cur)) return mem[cur];
	mem[cur] = ++t;
	int o = t;
	rep(i, 0, 9) {
		auto nxt = cur;
		rep(j, 0, 25) nxt[j] += prm[j][nxt[j]] == i + '0';
		bool ok = 1;
		rep(j, 0, 25) if(nxt[j] == prm[j].size()) ok = 0;
		if(ok) adj[o].emplace_back(i, dfs(nxt));
	}
	return o;
}

bool check(string str) {
	rep(i, 0, 25) {
		int j = 0;
		for(char ch : str) {
			if((j += ch == prm[i][j]) == prm[i].size()) break;
		}
		if(j == prm[i].size()) return 0;
	}
	return 1;
}

string lim;

inline int dfs(int p, int o, bool lim) {
	if(f[p][o][lim] != -1) return f[p][o][lim];
	if(p == ::lim.length()) return 1;
	ll res = 0;
	int r = lim ? ::lim[p] - '0' : 9;
	for(auto e : adj[o]) {
		int d = e.fi, v = e.se;
		if(d <= r) {
			res += dfs(p+1, v, lim && d == r);
		}
	}
	return f[p][o][lim] = res % P;
}

ll solve(string str) {
	memset(f, -1, sizeof f);
	lim = str;
	return dfs(0, 1, 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);

	dfs(vector<int>(26, 0));

	int t; cin >> t;
	while(t--) {
		cin >> l >> r;
		ll ans = (solve(r) - solve(l)) % P;
		if(check(l)) ++ans;
		cout << (ans + P) % P << "\n";
	}
}

