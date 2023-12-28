#include <bits/stdc++.h>
using namespace std;

const long long mod = 998244353;

int n, cnt, m, q, k;
vector <int> a, b, g[100005];
map <vector <int>, int> mp;
long long dp[22][100005];

inline void Dfs(vector <int> cur) {
	int sum = 0;
	for (int x : cur) sum += x;
	int siz = cur.size();
	//for (int i = 0;i < siz - 1;i++) assert(cur[i] >= cur[i + 1]);
	//for (int x : cur) assert(x);
	for (int i = 0;i < siz;i++) {
		if (i == siz - 1 || cur[i] > cur[i + 1]) {
			vector <int> nxt = cur;
			nxt[i]--;
			if (nxt.back() == 0) nxt.pop_back();
			if (!mp[nxt]) {
				mp[nxt] = ++cnt;
				Dfs(nxt);
			}
			g[mp[cur]].push_back(mp[nxt]);
		}
	}
	for (int i = 0;i < siz;i++) {
		if (i == 0 || cur[i] < cur[i - 1]) {
			vector <int> nxt = cur;
			nxt[i]++;
			if (sum + 1 <= 31) {
				if (!mp[nxt]) {
					mp[nxt] = ++cnt;
					Dfs(nxt);
				}
				g[mp[cur]].push_back(mp[nxt]);
			}
			
		}
	}
	vector <int> nxt = cur;
	nxt.push_back(1);
	if (sum + 1 <= 31) {
		if (!mp[nxt]) {
			mp[nxt] = ++cnt;
			Dfs(nxt);
		}
		g[mp[cur]].push_back(mp[nxt]);
	}
}

inline void Read() {
	cin >> n; a.resize(n, 0);
	for (int i = 0;i < n;i++) cin >> a[i];
	cin >> m; b.resize(m, 0);
	for (int i = 0;i < m;i++) cin >> b[i];
}

int main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	Read();
	mp[a] = ++cnt;
	Dfs(a);
	//cout << cnt << endl;
	dp[0][mp[a]] = 1;
	//cout << g[mp[a]].size() << endl;
	for (int k = 0;k < 20;k++) {
		for (int j = 1;j <= cnt;j++) {
			for (int v : g[j]) dp[k + 1][v] = (dp[k + 1][v] + dp[k][j]) % mod;
		}
	}
	cin >> q;
	while (q--) {
		cin >> k;
		cout << dp[k][mp[b]] << endl;
	}
	return 0;
}
