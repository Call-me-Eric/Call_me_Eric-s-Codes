#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1e6 + 5;

vector <int> adj[N];
set <pii> vec[N];
int col[N], mxdep[N], dep[N], wson[N], id[N];
int n; ll ans;

void dfs1(int u, int fa) {
    for (auto v : adj[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + 1; dfs1(v, u);
        if (mxdep[v] > mxdep[wson[u]]) wson[u] = v;
    }
    mxdep[u] = mxdep[wson[u]] + 1;
}

void dfs2(int u, int fa) {
    for (auto v : adj[u]) {
        if (v == fa) continue;
        dfs2(v, u);
    }
    if (!wson[u]) id[u] = u;
    else id[u] = id[wson[u]];
    for (auto v : adj[u]) {
        if (v == fa || v == wson[u]) continue;
        for (auto i : vec[id[v]]) {
            auto it = vec[id[u]].lower_bound(make_pair(i.first, 0));
            if (it != vec[id[u]].end() && it -> first == i.first) {
                int tmp = it -> second + i.second;
                vec[id[u]].erase(it);
                vec[id[u]].insert(make_pair(i.first, tmp));
            } else {
                vec[id[u]].insert(i);
            }
        }
    }
    if (col[u] == 0) {
        if (vec[id[u]].size() == 0) {
            print(-1, '\n');
            exit(0);
        }
        auto it = vec[id[u]].begin();
        int a = it -> first, b = it -> second;
        ans += it -> first - dep[u];
        vec[id[u]].erase(it);
        if (b > 1) vec[id[u]].insert(make_pair(a, b - 1));
    } else {
        vec[id[u]].insert(make_pair(dep[u], 1));
    }
}

int main() {
		freopen("wbtree.in","r",stdin);
	freopen("wbtree.out","w",stdout);
    read(n);
    for (int i = 1; i <= n; i++) read(col[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u); read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, 0); dfs2(1, 0);
    print(ans, '\n');
    return 0;
}
