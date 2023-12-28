#include<bits/stdc++.h>
#define ll long long
#define rep(i, x, y) for(int i = (x), stozzh = (y); i <= stozzh; i++)
#define irep(i, x, y) for(int i = (x), stozzh = (y); i >= stozzh; i--)
using namespace std;
using vint = vector<int>;
using pii = pair<int, int>;
#define let const auto
#define fi first
#define se second
#define pb emplace_back
#define il inline
int read() {
    int res = 0, flag = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') flag = -1; c = getchar(); }
    while(c >= '0' && c <= '9') res = res * 10 + c - '0', c = getchar();
    return res * flag;
}
template<typename T> il void tmax(T &x, const T y) { if(x < y) x = y; }
template<typename T> il void tmin(T &x, const T y) { if(x > y) x = y; }
const int N = 2e5 + 20;
int deg[N], sz[N], esz[N], fa[N], n, m, U[N];
bool has[N];
int findf(int x) { return fa[x] == x ? x : fa[x] = findf(fa[x]); }
signed main() {
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    n = read(), m = read();
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, m) {
        int u = read(), v = read();
        U[i] = u;
        deg[u]++, deg[v]++;
        fa[findf(u)] = findf(v);
    }
    rep(i, 1, n) {
        int x = findf(i);
        if(deg[i] > 3) return cout << "-1\n", 0;
        if(deg[i] == 3) has[x] = true;
        sz[x]++;
    }
    rep(i, 1, m) esz[findf(U[i])]++;
    ll ans1 = 0, ans2 = 0;
    rep(i, 1, n) if(findf(i) == i) {
        if(has[i] && esz[i] >= 4) return cout << "-1\n", 0;
        if(has[i] || sz[i] == esz[i]) ans2 += esz[i];
        else ans1 += 1ll * sz[i] * (sz[i] + 1) / 2;
    }
    if(ans2) cout << "1 " <<  ans2 << '\n';
    else cout << "0 " << ans1 << '\n';
    return 0;
}