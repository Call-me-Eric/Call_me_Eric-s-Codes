#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cstring>
#include<stack>

#define mem(ss) memset(ss,0,sizeof(ss))
#define rep(d, s, t) for(int d=s;d<=t;d++)
#define rev(d, s, t) for(int d=s;d>=t;d--)
#define inf 0x3f3f3f3f
typedef long long ll;
typedef long double ld;
typedef double db;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
const ll mod = 1e9 + 7;
const int N = 1e5 + 10;
#define io_opt ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int fa[N][1 << 5];
int n, m, dep[N];
ll dis[N];
struct Edge {
    int v, w;
};
vector<Edge> G[N];

void dfs(int u, int father) {
    fa[u][0] = father;
    for (int i = 1; i <= 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (Edge &e:G[u])
        if (e.v != father) {
            dis[e.v] = dis[u] + e.w;
            dep[e.v] = dep[u] + 1;
            dfs(e.v, u);
        }
}

inline void init() {
    int u, v, c;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &c);
        G[u].push_back(Edge{v, c});
        G[v].push_back(Edge{u, c});
    }
    dis[1] = dep[1] = 0;
    dfs(1, 0);
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) std::swap(u, v);
    int k = dep[v] - dep[u];
    for (int i = 20; i >= 0; i--) {
        if ((k >> i) & 1)
            v = fa[v][i];
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main() {
    int q, u, v;
    cin >> n >> q;
    init();
    while (q--) {
        cin >> u >> v;
        cout << dis[u] + dis[v] - 2 * dis[lca(u, v)] << endl;
    }
    return 0;
}


