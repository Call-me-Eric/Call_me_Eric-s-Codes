#include <bits/stdc++.h>
#define int long long 
using namespace std;

inline int read() {
    int x = 0, f = 0; char ch = getchar();
    while(ch < '0' or ch > '9') f |= (ch == '-'), ch = getchar();
    while(ch >= '0' and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}
int __stk[128], __top;
inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    do { __stk[++__top] = x % 10, x /= 10; } while(x);
    while(__top) putchar(__stk[__top--] + '0');
}
bool stmer;
const int N = 710, mod = 998244353;
void add(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
void mul(int &x, int y) { x = x * y % mod; }
int q_pow(int x, int k) {
    int res = 1;
    for(; k; k >>= 1, mul(x, x))
        if(k & 1) mul(res, x);
    return res;
}
int n, q;
int a[N][N], b[N][N], val[N];
bool vis[N];
void mul(int *p, int k) {
    for(int i = 0; i <= n; i++) mul(p[i], k);
}
void del(int x, int y, int k) {
    for(int i = 0; i <= n; i++) add(b[x][i], mod - b[y][i] * k % mod);
}
void solve() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) b[i][j] = a[i][j];
        vis[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) if(b[j][i] and !vis[j]) {
            swap(b[i], b[j]); break;
        } if(b[i][i]) mul(b[i], q_pow(b[i][i], mod - 2)), vis[i] = 1;
        for(int j = i + 1; j < n; j++) if(b[j][i]) del(j, i, b[j][i]);
    } bool f1 = 0;
    for(int i = n - 1; i + 1; i--) {
        val[i] = b[i][n];
        for(int j = 0; j < i; j++) if(b[j][i]) del(j, i, b[j][i]);
        if(!b[i][i]) f1 = 1, val[i] = -1; bool f = 0;
        for(int j = 0; j < n; j++) if(b[i][j]) f = 1;
        if(!f and b[i][n]) return puts("No"), void();
    }
    if(f1) puts("Many");
    else {
        for(int i = 0; i < n; i++) write(val[i]), putchar(' ');
        putchar('\n');
    }
}
bool edmer;
signed main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    n = read(), q = read();
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= n; j++) a[i][j] = read();
    solve();
    while(q--) {
        int x = read() - 1;
        for(int i = 0; i <= n; i++) a[x][i] = read();
        solve();
    }
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}