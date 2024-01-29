#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int N = 705;

int n, T, ans[N];
vector<int> a[N], b[N];

inline int add(int x, int y) {x += y; return x >= mod ? x - mod : x;}
inline int del(int x, int y) {x -= y; return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {x = add(x, y);}
inline void Del(int &x, int y) {x = del(x, y);}

inline int qpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
        y >>= 1;
    }
    return res;
}

int Gauss() {
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    int now = 1; bool tf = false;
    for (int i = 1; i <= n; ++i) {
        bool pd = false;
        for (int j = now; j <= n; ++j) {
            if (!b[j][i]) continue;
            pd = true; swap(b[now], b[j]); break;
        }
        if (!pd) {tf = true; continue;}
        for (int j = 1; j <= n; ++j) {
            if (j == now) continue;
            int tmp = 1ll * b[j][i] * qpow(b[now][i], mod - 2) % mod;
            for (int k = i; k <= n + 1; ++k) Del(b[j][k], 1ll * tmp * b[now][k] % mod);
        }
        now++;
    }
    for (int i = 1; i <= n; ++i) {
        bool pd = false;
        for (int j = 1; j <= n; ++j) pd |= b[i][j];
        if (!pd && b[i][n + 1]) return -1;
    }
    if (tf) return 0;
    for (int i = 1; i <= n; ++i) ans[i] = 1ll * b[i][n + 1] * qpow(b[i][i], mod - 2) % mod;
    return 1;
}

void print() {
    int res = Gauss();
    if (res == -1) puts("No");
    else if (res == 0) puts("Many");
    else {
        for (int i = 1; i < n; ++i) printf("%d ", ans[i]);
        printf("%d\n", ans[n]);
    }
}

int main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; ++i) {
        a[i].resize(n + 2);
        for (int j = 1; j <= n + 1; ++j)
            scanf("%d", &a[i][j]);
    }
    print();
    int id;
    while (T--) {
        scanf("%d", &id);
        for (int i = 1; i <= n + 1; ++i) scanf("%d", &a[id][i]);
        print();
    }
    return 0;
}
