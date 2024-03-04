#include <bits/stdc++.h>
#pragma GCC optimize(2)
const int mod = 998244853;
using namespace std;
int n, GCD, LCM, Q, p[2][9], c[2][9], m[2], ys[770][9], N, f[256][256][770], a[9], g[256][256][770];
inline int mypow(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = 1ll * ans * x % mod;
        y >>= 1;
        x = 1ll * x * x % mod;
    }
    return ans;
}
inline void dfs(int x, int now) {
    if (x == m[1] + 1) {
        if (now > n)
            return;
        ys[++N][0] = now;
        for (int i = 1; i <= m[1]; ++i) ys[N][i] = a[i];
        return;
    }
    int Pow = 1;
    for (int i = 0; i <= c[1][x]; ++i) {
        a[x] = i;
        dfs(x + 1, now * Pow);
        Pow *= p[1][x];
    }
}
inline void add(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
int main() {
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    scanf("%d%d%d%d", &n, &GCD, &LCM, &Q);
    int gcd = GCD;
    if (LCM % GCD) {
        for (int i = 0; i <= Q; ++i) puts("0");
        return 0;
    }
    if (LCM == 1) {
        for (int i = 0; i <= Q; ++i) puts("1");
        return 0;
    }
    for (int i = 2; i * i <= LCM; ++i) {
        if (LCM % i == 0) {
            p[1][++m[1]] = i;
            while (LCM % i == 0) ++c[1][m[1]], LCM /= i;
        }
    }
    if (LCM != 1)
        p[1][++m[1]] = LCM, c[1][m[1]] = 1;
    m[0] = m[1];
    for (int i = 1; i <= m[0]; ++i) {
        p[0][i] = p[1][i];
        while (GCD % p[0][i] == 0) GCD /= p[0][i], ++c[0][i];
    }
    dfs(1, 1);
    f[0][0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < (1 << m[0]); ++j)
            for (int k = 0; k < (1 << m[1]); ++k) f[j][k][i] = f[j][k][i - 1];
        if (ys[i][0] % gcd)
            continue;
        int jjxsm = 0, jjxmymq = 0;
        for (int j = 1; j <= m[0]; ++j)
            if (ys[i][j] == c[0][j])
                jjxsm |= (1 << (j - 1));
        for (int j = 1; j <= m[1]; ++j)
            if (ys[i][j] == c[1][j])
                jjxmymq |= (1 << (j - 1));
        for (int j = 0; j < (1 << m[0]); ++j)
            for (int k = 0; k < (1 << m[1]); ++k) add(f[j | jjxsm][k | jjxmymq][i], f[j][k][i - 1]);
    }
    g[0][0][N + 1] = 1;
    for (int i = N; i; --i) {
        for (int j = 0; j < (1 << m[0]); ++j)
            for (int k = 0; k < (1 << m[1]); ++k) g[j][k][i] = g[j][k][i + 1];
        if (ys[i][0] % gcd)
            continue;
        int jjxsm = 0, jjxmymq = 0;
        for (int j = 1; j <= m[0]; ++j)
            if (ys[i][j] == c[0][j])
                jjxsm |= (1 << (j - 1));
        for (int j = 1; j <= m[1]; ++j)
            if (ys[i][j] == c[1][j])
                jjxmymq |= (1 << (j - 1));
        for (int j = 0; j < (1 << m[0]); ++j)
            for (int k = 0; k < (1 << m[1]); ++k) add(g[j | jjxsm][k | jjxmymq][i], g[j][k][i + 1]);
    }
    printf("%d\n", f[(1 << m[0]) - 1][(1 << m[1]) - 1][N]);
    if (!Q)
        return 0;
    int x, ans[770];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < m[0]; ++i) {
        for (int j = (1 << m[0]) - 1; j >= 0; --j) {
            if (!(j & (1 << i))) {
                for (int k = 0; k < (1 << m[1]); ++k) {
                    for (int p = 2; p <= N + 1; ++p) add(g[j][k][p], g[j | (1 << i)][k][p]);
                }
            }
        }
    }
    for (int i = 0; i < m[1]; ++i) {
        for (int j = (1 << m[1]) - 1; j >= 0; --j) {
            if (!(j & (1 << i))) {
                for (int k = 0; k < (1 << m[0]); ++k) {
                    for (int p = 2; p <= N + 1; ++p) add(g[k][j][p], g[k][j | (1 << i)][p]);
                }
            }
        }
    }
    for (int t = 1; t <= N; ++t) {
        int jjxsm = 0, jjxmymq = 0;
        for (int j = 1; j <= m[0]; ++j)
            if (ys[t][j] == c[0][j])
                jjxsm |= (1 << (j - 1));
        for (int j = 1; j <= m[1]; ++j)
            if (ys[t][j] == c[1][j])
                jjxmymq |= (1 << (j - 1));
        for (int i = 0; i < (1 << m[0]); ++i) {
            for (int j = 0; j < (1 << m[1]); ++j) {
                int I = i | jjxsm, J = j | jjxmymq;
                ans[t] = (ans[t] + 1ll * f[i][j][t - 1] *
                                       g[((1 << m[0]) - 1) ^ I][((1 << m[1]) - 1) ^ J][t + 1] % mod) %
                         mod;
            }
        }
    }
    while (Q--) {
        scanf("%d", &x);
        if (x % gcd) {
            puts("0");
            continue;
        }
        int pos = 0;
        for (int i = 1; i <= N; ++i)
            if (ys[i][0] == x)
                pos = i;
        if (!pos) {
            puts("0");
            continue;
        }
        printf("%d\n", ans[pos]);
    }
}
