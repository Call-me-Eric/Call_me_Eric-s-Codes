# include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
# define fi first
# define se second
const int MAXN = 255;
const int MAXM = MAXN * MAXN;
int n[3], tol, m;
int eu[MAXM], ev[MAXM], ec[MAXM];
struct Edge{
	int fi, se, id;
	Edge(int fi = 0, int se = 0, int id = 0): fi(fi), se(se), id(id){}
};
vector<Edge> a[3];
int cnt[3];
bool flg[3][MAXN];
struct DSU{
	int fa[MAXN];
	void init(){
		for (int i = 1; i <= tol; i++) fa[i] = i;
	}
	int fdrt(int u){
		if (fa[u] == u) return u;
		else return fa[u] = fdrt(fa[u]);
	}
	bool chk(int u, int v){
		return fdrt(u) == fdrt(v);
	}
	void mrg(int u, int v){
		u = fdrt(u);
		v = fdrt(v);
		if (u != v) fa[u] = v;
	}
} dsu0, dsu11, dsu12, dsu21, dsu22, dsu23;
void wrk0(){
	for (Edge e : a[0]){
		if (dsu0.chk(e.fi, e.se)) continue;
		cnt[0]++;
		flg[0][e.id] = true;
		dsu0.mrg(e.fi, e.se);
	}
	for (Edge e : a[1]){
		if (dsu0.chk(e.fi, e.se)) continue;
		if (dsu12.chk(dsu0.fdrt(e.fi), dsu0.fdrt(e.se))) continue;
		cnt[1]++;
		flg[1][e.id] = true;
		dsu12.mrg(dsu0.fdrt(e.fi), dsu0.fdrt(e.se));
	}
}
bool slv(){
	dsu0.init();
	dsu11.init();
	dsu12.init();
	wrk0();
	// cerr << "cnt " << cnt[0] << ' ' << cnt[1] << '\n';
	if (cnt[0] < n[0] || cnt[1] > n[1]) return false;
	if (cnt[0] == n[0] && cnt[1] == n[1]) return true;
	for (Edge e : a[1]){
		if (!dsu0.chk(e.fi, e.se)) continue;
		if (dsu11.chk(e.fi, e.se)) continue;
		cnt[1]++;
		flg[1][e.id] = true;
		cnt[0]--;
		dsu11.mrg(e.fi, e.se);
		if (cnt[0] == n[0] && cnt[1] == n[1]) return true;
	}
	return cnt[0] == n[0] && cnt[1] == n[1];
}
DSU dsu4;
bool chk(int s){
	cnt[0] = cnt[1] = cnt[2] = 0;
	dsu4.init();
	for (int i = 1; i <= m; i++){
		if (!((s >> (i - 1)) & 1)) continue;
		if (++cnt[ec[i]] > n[ec[i]]) return false;
		if (dsu4.chk(eu[i], ev[i])) return false;
		dsu4.mrg(eu[i], ev[i]);
	}
	return cnt[0] == n[0] && cnt[1] == n[1] && cnt[2] == n[2];
}
int slv1(){
	for (int s = 1; s < (1 << m); s++){
		if (chk(s)) return s;
	}
	return -1;
}
mt19937 mrd(time(0));
int main(){
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n[0] >> n[1] >> n[2] >> m;
	tol = n[0] + n[1] + n[2] + 1;
	for (int i = 1; i <= m; i++){
		int u, v;
		char c;
		cin >> u >> v >> c;
		eu[i] = u; ev[i] = v;
		if (c == 'r') ec[i] = 0;
		if (c == 'g') ec[i] = 1;
		if (c == 'b') ec[i] = 2;
		a[ec[i]].push_back(Edge(u, v, i));
	}
	if (tol <= 5){
		int nm = slv1();
		if (nm == -1) cout << "NO\n";
		else {
			cout << "YES\n";
			for (int i = 1; i <= m; i++) cout << ((nm >> (i - 1)) & 1);
			cout << '\n';
		}
		return 0;
	}
	if (n[2] == 0){
		if (!slv()) cout << "NO\n";
		else {
			cout << "YES\n";
			dsu4.init();
			for (int i = 1; i <= m; i++) if (flg[1][i]) dsu4.mrg(eu[i], ev[i]);
			for (int i = 1; i <= m; i++) if (flg[0][i] && dsu4.chk(eu[i], ev[i])) flg[0][i] = false;
			for (int i = 1; i <= m; i++) cout << (flg[1][i] || flg[0][i]);
			cout << '\n';
		}
		return 0;
	}
	cout << "YES\n";
	dsu4.init();
	for (int j = 0; j <= 2; j++){
		shuffle(a[j].begin(), a[j].end(), mrd);
		for (Edge i : a[j]){
			if (cnt[j] >= n[j]) break;
			if (dsu4.chk(i.fi, i.se)) continue;
			flg[0][i.id] = true;
			dsu4.mrg(i.fi, i.se);
		}
	}
	for (int i = 1; i <= m; i++) cout << flg[0][i];
	cout << '\n';
	return 0;
}
/*
2 1 1 5
1 2 r
2 3 r
1 3 r
2 4 g
2 5 b
*/
