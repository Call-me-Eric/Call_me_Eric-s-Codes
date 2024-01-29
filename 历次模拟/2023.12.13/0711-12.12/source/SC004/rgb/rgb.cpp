#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, x, y) for(int i = (x), stOzzh = (y); i <= stOzzh; ++i)
#define irep(i, x, y) for(int i = (x), stOzzh = (y); i >= stOzzh; --i)
#define pb emplace_back
#define il inline
#define fi first
#define se second
#define let const auto
using pii = pair<int, int>;
using vint = vector<int>; 
const int N = 255, M = N * N / 2;
bool in[M];
int n, m, U[M], V[M], col[M], has[3], need[3];
il int to(int e, int u) { return U[e] ^ V[e] ^ u; }

namespace build {
int fa[N];
int findf(int x) { return fa[x] == x ? fa[x] : findf(fa[x]); }
bool adde(int u, int v) {
	u = findf(u), v = findf(v);
	if(u != v) return fa[u] = v, true;
	return false;
}
int solve(int c, bool op = true) {
	rep(i, 0, 2) has[i] = 0;
	rep(i, 1, n) fa[i] = i;
	rep(i, 1, m) if((col[i] == c) == op) in[i] = adde(U[i], V[i]);
	rep(i, 1, m) if((col[i] == c) != op) in[i] = adde(U[i], V[i]);
	rep(i, 1, m) if(in[i]) has[col[i]]++;
	return has[c];
} 
}


using info = array<int, 3>;
vint G[N];
void dfs(int u, int fa, info *f) {
	for(int e : G[u]) {
		int v = to(e, u);
		if(v == fa) continue;
		f[v] = f[u], f[v][col[e]] = e;
		dfs(v, u, f);
	} 
}
info f[N][N];
void rebuild() {
	rep(i, 1, n) G[i].clear();
	rep(i, 1, m) if(in[i]) G[U[i]].pb(i), G[V[i]].pb(i);
	rep(i, 1, n) {
		f[i][i] = info{0, 0, 0};
		dfs(i, 0, f[i]);
	}
}

bool change(int cfr, int cto) {
	rep(i, 1, m) if(col[i] == cto) {
		int t = f[U[i]][V[i]][cfr];
		if(t) {
			has[cfr]--, has[cto]++;
			in[t] = false, in[i] = true;
			rebuild();
			return true;
		}
	}
	return false;
}
signed main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	ios::sync_with_stdio(0);
	rep(i, 0, 2) cin >> need[i];
	n = accumulate(need, need + 3, 1);
	cin >> m;
	auto GG = [&]() { cout << "No\n"; exit(0); };
	string dict = "rgb";
	rep(i, 1, m) {
		char c;
		cin >> U[i] >> V[i] >> c;
		col[i] = dict.find(c);
	}
	rep(c, 0, 2) if(build::solve(c, true) < need[c] || build::solve(c, false) > need[c]) GG();
	build::solve(2), rebuild();
	while(has[2] > need[2]) if(!change(2, 0) && !change(2, 1)) GG();
	int more = has[1] > need[1], less = more ^ 1;
	while(has[more] > need[more]) {
		if(change(more, less)) continue;
		if(!change(more, 2) || !change(2, less)) GG();
	}
	cout << "Yes\n";
	rep(i, 1, m) cout << in[i];
	cout << '\n';
	return 0;
}
