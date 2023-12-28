#include <bits/stdc++.h>
using namespace std;
constexpr int B = 26;
using arr = array<int, B>;
constexpr int S = 500010, N = 20, mod = 998244353;
arr ban{2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
array<vector<int>, B> dig;
int power[10];
int cnt, tot, G[S][10], col[S];
vector<int> vec[S];
int tr[N][10] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,4,0,1,0,4,1,4,4,0,0,4,0,4,0,4,0,1,4,0,0,4,0,1,0,2,1,4,0,0,0,4,0,4,0,4,0,5,4,0,0,17,0,15,0,12,8,4,0,0,0,4,0,4,0,4,4,2,4,0,0,4,0,4,0,4,0,3,4,0,0,14,0,1,0,7,1,1,0,0,0,6,0,1,0,4,1,4,0,0,0,4,0,6,0,4,4,16,0,0,0,6,0,16,0,4,1,12,4,0,0,4,0,4,0,4,0,9,0,0,0,6,0,1,0,4,1,4,0,0,0,4,0,10,0,4,4,18,0,0,0,6,0,11,0,4,1,13,0,0,0,6,0,1,0,4,1,4,0,0,0,4,0,17,0,4,4,16,0,0,0,6,0,1,0,4,1};
int init() {
	for(int i = 0; i < B; i ++) {
		for(int x = ban[i]; x; x /= 10) dig[i].emplace_back(x % 10);
		reverse(dig[i].begin(), dig[i].end());
	}
	power[0] = 1;
	for(int i = 1; i < 10; i ++) {
		power[i] = power[i - 1] * 10;
	}
	arr st{};
	queue<arr> q;
	q.emplace(st);
	map<arr, int> id;
	id[st] = ++ cnt;
	while(!q.empty()) {
		arr u = q.front(); q.pop();
		for(int i = 0; i < 10; i ++) {
			arr v = u;
			int ok = 1;
			for(int j = 0; j < B; j ++) {
				if(dig[j][v[j]] == i) v[j] ++;
				if(v[j] == dig[j].size()) ok = 0;
			}
			if(ok) {
				if(!id.count(v)) {
					q.emplace(v);
					id[v] = ++ cnt;
				}
				G[id[u]][i] = id[v];
			} else {
				G[id[u]][i] = 0;
			}
		}
	}
	fill(col + 1, col + cnt + 1, 1);
	vec[1].resize(cnt);
	iota(vec[1].begin(), vec[1].end(), 1);
	tot = 1;
	while(1) {
		int upd = 0;
		for(int c = 0; c < 10; c ++) {
			static int vis[S];
			int last = tot;
			for(int i = 1; i <= last; i ++) {
				for(auto u : vec[i]) {
					int v = col[G[u][c]];
					if(!vis[v]) vis[v] = ++ tot;
					vec[vis[v]].emplace_back(u);
				}
				swap(vec[i], vec[tot]);
				for(auto u : vec[tot]) {
					int v = col[G[u][c]];
					vis[v] = 0;
				}
				vec[tot].clear();
				tot --;
			}
			upd |= tot != last;
			for(int i = 1; i <= tot; i ++) {
				for(auto u : vec[i]) col[u] = i;
			}
		}
		if(!upd) break;
	}
	for(int i = 1; i <= cnt; i ++) {
		for(int j = 0; j < 10; j ++) if(G[i][j]) {
			if(tr[col[i]][j]) assert(tr[col[i]][j] == col[G[i][j]]);
			tr[col[i]][j] = col[G[i][j]];
		}
	}
	return col[1];
}
int add(int a, int b) {return a += b - mod, a += a >> 31 & mod;}
void upd(int &a, int b) {a += b - mod, a += a >> 31 & mod;}
int main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(0);
	int rt = 5;	tot = 18;
	int T;
	for(cin >> T; T; T --) {
		string l, r;
		cin >> l >> r;
		for(int i = l.size() - 1; ; i --) {
			if(l[i] == '0') l[i] = '9';
			else {l[i] --; break;}
		}
		auto solve = [&] (string str) {
			int n = str.size();
			vector<int> a(n);
			for(int i = 0; i < n; i++) a[i] = str[i] - '0';
			static int dp[2][N], new_dp[2][N];
			memset(dp, 0, sizeof dp);
			dp[1][rt] = 1;
			for(int i = 0; i < n; i ++) {
				memset(new_dp, 0, sizeof new_dp);
				for(int j = 0; j < 2; j ++) {
					int lim = j ? a[i] : 9;
					for(int u = 1; u <= tot; u ++) if(dp[j][u]) {
						for(int c = 0; c <= lim; c ++){
							upd(new_dp[j & (c == lim)][tr[u][c]], dp[j][u]);
						}
					}
				}
				swap(dp, new_dp);
			}
			int ans = 0;
			for(int i = 1; i <= tot; i ++) upd(ans, dp[0][i]), upd(ans, dp[1][i]);
			return ans;
		};
		cout << add(solve(r), mod - solve(l)) << '\n';
	}
	return 0;
}