#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 710, mod = 998244353;
int Add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int Sub(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
int Mul(int x, int y) { return 1ll * x * y % mod; }
int Qpow(int a, int b) {
    int base = 1;
    while (b) {
        if (b & 1) base = Mul(base, a);
        a = Mul(a, a), b >>= 1;
    }
    return base;
}
int Inv(int x) { return Qpow(x, mod - 2); }
int N, Q, a[MAXN][MAXN], b[MAXN][MAXN];
void solve() {
    for (int i = 1; i <= N; i++) {
        int now = i;
        while (!a[now][i] and now <= N) ++now;
        if (now != N + 1) {
            for (int j = 1; j <= N + 1; j++)
                swap(a[i][j], a[now][j]);
            int inv = Inv(a[i][i]);
            for (int j = i; j <= N + 1; j++)
                a[i][j] = Mul(a[i][j], inv);
            for (int j = 1; j <= N; j++) if (j != i) {
                int mul = a[j][i];
                for (int k = i; k <= N + 1; k++) 
                    a[j][k] = Sub(a[j][k], Mul(mul, a[i][k]));
            }
        }
    }
    bool flag1 = false, flag2 = false;
    for (int i = 1; i <= N; i++) {
        if (a[i][i] == 0 and a[i][N + 1]) flag1 = true;
        if (a[i][i] == 0 and a[i][N + 1] == 0) flag2 = true;
    }
    if (flag1) printf("No\n");
    else if (flag2) printf("Many\n");
    else {
        for (int i = 1; i <= N; i++)
            printf("%d%c", a[i][N + 1], " \n"[i == N]);
    }
}
int main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    N = read(), Q = read();
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N + 1; j++) a[i][j] = b[i][j] = read();
    solve();
    while (Q--) {
        int x = read();
        for (int i = 1; i <= N + 1; i++) b[x][i] = read();
        for (int i = 1; i <= N; i++) 
            for (int j = 1; j <= N + 1; j++) a[i][j] = b[i][j];
        solve();
    }
}
