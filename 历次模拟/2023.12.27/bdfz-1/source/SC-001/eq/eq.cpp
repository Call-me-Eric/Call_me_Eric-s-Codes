#include <bits/stdc++.h>
using namespace std;

#define rep(i, x, y) for(int i = (x), faq = (y); i <= faq; i++)
#define irep(i, x, y) for(int i = (x), faq = (y); i >= faq; i--)

using ll = long long;

int read() {
    int res = 0, flag = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') flag = -1; c = getchar(); }
    while(c >= '0' && c <= '9') res = res * 10 + c - '0', c = getchar();
    return res * flag;
}
const int N = 705, P = 998244353;
int ksm(ll x, int y = P - 2) {
    ll res = 1;
    for(; y; y >>= 1, (x *= x) %= P) if(y & 1) (res *= x) %= P;
    return res;
}
constexpr void fix(int &x) { x = x + ((x >> 31) & P); }
int n;
struct node {
    int mem[N], dt;
    int& operator [](const int x) { return mem[x]; }
    int operator [](const int x) const { return mem[x]; }
};
node mp[N];
void ins(node &a) {
    rep(i, 1, n + 1) if(a[i]) {
        if(!mp[i].dt) { mp[i] = a; break; }
        if(mp[i].dt < a.dt) swap(mp[i], a);
        ll prod = 1ll * a[i] * ksm(mp[i][i]) % P;
        rep(j, i, n + 1) fix(a[j] -= prod * mp[i][j] % P);
    }
}
int ans[N];
void solve(int nt) {
    if(mp[n + 1].dt >= nt) return cout << "No\n", void();
    rep(i, 1, n) if(mp[i].dt < nt) return cout << "Many\n", void();
    irep(i, n, 1) {
        int res = mp[i][n + 1];
        rep(j, i + 1, n) fix(res -= 1ll * mp[i][j] * ans[j] % P);
        ans[i] = 1ll * res * ksm(mp[i][i]) % P;
    }
    rep(i, 1, n) cout << ans[i] << ' ';
    cout << "\n";
}

int q, id[N];
node in[N * 2];
signed main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    n = read(), q = read();
    rep(i, 1, n) {
        id[i] = i, in[i].dt = 114514;
        rep(j, 1, n + 1) in[i][j] = read();
    }
    rep(i, n + 1, n + q) {
        int del = read();
        in[id[del]].dt = i - 1, in[i].dt = 114514;
        id[del] = i;
        rep(j, 1, n + 1) in[i][j] = read();
    }
    rep(i, 1, n - 1) ins(in[i]);
    rep(i, n, n + q) ins(in[i]), solve(i);
    return 0;
}
