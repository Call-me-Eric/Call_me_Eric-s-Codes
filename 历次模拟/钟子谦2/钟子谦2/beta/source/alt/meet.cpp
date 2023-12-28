// Awwawa! Dis cold yis ratten buy Pikachu!
#pragma optimize(3)
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define mod 998244353
template <typename T>
bool chkmin(T &a, T b) { return (b < a) ? a = b, 1 : 0; }
template <typename T>
bool chkmax(T &a, T b) { return (b > a) ? a = b, 1 : 0; }
using namespace std;
const int maxn = 300005;
vector<pi> eg[maxn];
void ade(int u, int v, int w) {
    eg[u].pb(mp(v, w));
    eg[v].pb(mp(u, w));
}
int findw(int u, int v) {
    for (auto i : eg[u]) 
        if (i.fi == v) return i.se;
}
void del(int u, int v, int w) {
    for (int i = 0; i < eg[u].size(); i++) {
        if (eg[u][i].fi == v && eg[u][i].se == w) {
            eg[u].erase(eg[u].begin() + i);
            break;
        }
    }
    for (int i = 0; i < eg[v].size(); i++) {
        if (eg[v][i].fi == u && eg[v][i].se == w) {
            eg[v].erase(eg[v].begin() + i);
            break;
        }
    }
}

int n;
ll ans = 1e18;
ll dep[maxn];
int sz[maxn], fa[maxn];
vi vis;
void dfs(int a) {
    vis.pb(a);
    sz[a] = 1;
    for (auto i : eg[a]) {
        if (i.fi == fa[a]) continue;
        fa[i.fi] = a;
        dep[i.fi] = dep[a] + i.se;
        dfs(i.fi);
        sz[a] += sz[i.fi];
    }
}
void dodfs(int u) {
    fa[u] = 0, dep[u] = 0; vis.clear(); vis.reserve(n);
    dfs(u);
}
map<pair<int, int>, int> calc;
void work(int u, int v) {
    if (u > v) swap(u, v);
    if (calc.count(mp(u, v))) return;
    calc[mp(u, v)] = 1;
    // work wi
    int w = findw(u, v);
    del(u, v, w);
    int h[2] = {u, v};
    int cent[2] = {0, 0};
    ll sum = 0;
    for (int i = 0; i < 2; i++) {
        auto j = h[i];
        dodfs(j);
        int s = sz[j], mpl = 0;
        for (auto v : vis) 
            if (sz[v] * 2 >= sz[j] && (mpl == 0 || sz[v] < sz[mpl])) 
                mpl = v;
        cent[i] = mpl;
        dodfs(cent[i]);
        for (auto v : vis) sum += dep[v];
    }
    chkmin(ans, sum);
    ade(u, v, w);
    dodfs(cent[0]);
    vi path;
    int cur = cent[1];
    while (cur) {
        path.pb(cur);
        cur = fa[cur];
    }
    ll len = dep[cent[1]];
    int lastv = 0;
    for (auto v : path) 
        if ((len - dep[v]) * 2 <= len ) lastv = v;
    work(lastv, fa[lastv]);
}
int main() {
	mt19937 rnd;
//    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    freopen("meet.in", "r", stdin);
    freopen("meet.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ade(u, v, w);
    }
    for (int j = 0; j < ((n<5000)?100:5); j++) {
        int u = rnd() % n + 1;
        int v = eg[u][rnd() % eg[u].size()].fi;
        work(u, v);
    }
    cout << ans << endl;
    return 0;
}

