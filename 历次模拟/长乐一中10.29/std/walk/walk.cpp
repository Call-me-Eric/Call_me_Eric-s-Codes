#include <bits/stdc++.h>

const int N = 1001000;
const int mod = 998244353;

struct node {
    int k, b;
};

std::vector<node> f[N];

int n, k;

int p[N];

int head[N], ver[N * 2], Next[N * 2], tot;
void add_edge(int u, int v) {
    ver[++ tot] = v, Next[tot] = head[u], head[u] = tot;
}

int du[N];

int mypow(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
    }
    return res;
}

void solve(int u, int fa, int ke) {
    f[u][ke].b = (1ll * f[fa][ke].b * f[u][ke].k + f[u][ke].b) % mod;
    f[u][ke].k = 0;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == fa) continue;
        solve(v, u, ke);
    }
}

void dp(int u, int fa, int ke) {
    if (du[u] == 1 && u != 1) {
        int inv = 1ll * mypow(mod + 1 - p[u], mod - 2) * p[u] % mod;
        f[u][ke].k = 1;
        f[u][ke].b = (f[fa][ke - 1].b + 1ll * inv * f[u][ke - 1].b) % mod;
        return;
    }

    if (u == 1) {
        for (int i = head[u]; i; i = Next[i]) {
            int v = ver[i];
            dp(v, u, ke);
        }

        for (int i = head[u]; i; i = Next[i]) {
            int v = ver[i];
            solve(v, u, ke);
        }
        return;
    }

    int inv = 1ll * (mod + 1 - p[u]) * mypow(du[u], mod - 2) % mod;
    int sumv = 0, sumk = 0;

    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == fa) continue;

        dp(v, u, ke);
        sumv = (sumv + f[v][ke].b) % mod;
        sumv = (sumv + f[v][ke - 1].b) % mod;
        sumk = (sumk + f[v][ke].k) % mod;
    }

    sumv = 1ll * inv * (sumv + f[fa][ke - 1].b) % mod;
    sumv = (1ll * p[u] * f[u][ke - 1].b + sumv) % mod;

    int K = ((1 - 1ll * inv * sumk % mod + mod) % mod - p[u] + mod) % mod;

    int inv2 = mypow(K, mod - 2);

    f[u][ke].b = 1ll * sumv * inv2 % mod;
    f[u][ke].k = 1ll * inv * inv2 % mod;
}

namespace NTT {
    int n;

    int f[N], g[N], S[N], rev[N];

    int fac[N], inv[N];

    void add(int &x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    }

    void dec(int &x, int y) {
        x -= y;
        if (x < 0) x += mod;
    }

    int power(int a, int b) {
        int res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = 1ll * res * a % mod;
            a = 1ll * a * a % mod;
        }
        return res;
    }

    int m = 0;

    void NTT(int *A) {
        for (int i = 0; i < m; ++ i)
            if (i < rev[i]) std::swap(A[i], A[rev[i]]);

        for (int k = 1; k < m; k <<= 1) {
            int omega = power(3, (mod - 1) / (k << 1));
            for (int i = 0; i < m; i += (k << 1)) {
                int x = 1;
                for (int j = 0; j < k; ++ j, x = 1ll * x * omega % mod) {
                    int u = A[i + j], v = 1ll * x * A[i + j + k] % mod;
                    add(A[i + j] = u, v), dec(A[i + j + k] = u, v);
                }
            }
        }
    }

    void INTT(int *A) {
        for (int i = 0; i < m; ++ i)
            if (i < rev[i]) std::swap(A[i], A[rev[i]]);

        for (int k = 1; k < m; k <<= 1) {
            int omega = power(3, (mod - 1) / (k << 1));
            omega = power(omega, mod - 2);
            for (int i = 0; i < m; i += (k << 1)) {
                int x = 1;
                for (int j = 0; j < k; ++ j, x = 1ll * x * omega % mod) {
                    int u = A[i + j], v = 1ll * x * A[i + j + k] % mod;
                    add(A[i + j] = u, v), dec(A[i + j + k] = u, v);
                }
            }
        }

        int mul = power(m, mod - 2);
        for (int i = 0; i < m; ++ i)
            A[i] = 1ll * A[i] * mul % mod;
    }

    void main() {
        fac[0] = 1;
        for (int i = 1; i <= n; ++ i)
            fac[i] = 1ll * i * fac[i - 1] % mod;

        inv[n] = power(fac[n], mod - 2);
        for (int i = n - 1; i >= 0; -- i)
            inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;

        for (int i = 0; i <= n; ++ i) 
            i & 1 ? dec(f[i] = mod, inv[i]) : add(f[i], inv[i]);

        for (int i = 0; i <= n; ++ i) 
            g[i] = 1ll * inv[i] * power(i, n) % mod;

        while ((1 << m) <= (n << 1)) m ++;

        for (int i = 1; i < (1 << m); ++ i)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));

        m = 1 << m;
        NTT(f), NTT(g);

        for (int i = 0; i < m; ++ i)
            S[i] = 1ll * f[i] * g[i] % mod;

        INTT(S);
    }   
}

int main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    
    scanf("%d%d", &n, &k);

    if (! k) {
        for (int i = 1; i < n; ++ i)
            puts("1");
        return 0;
    }

    for (int i = 1; i < n; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add_edge(u, v), add_edge(v, u);
        ++ du[u], ++ du[v];
    }

    int inv1000000 = mypow(1000000, mod - 2);

    for (int i = 2; i <= n; ++ i) {
        scanf("%d", &p[i]);
        p[i] = 1ll * p[i] * inv1000000 % mod;
    }

    for (int i = 1; i <= n; ++ i) {
        f[i].resize(k + 1);
        f[i][0].b = 1;
    }

    for (int i = 1; i <= k; ++ i)
        dp(1, 0, i);

    NTT::n = k;
    NTT::main();

    for (int i = 2; i <= n; ++ i) {
        int fc = 1, ans = 0;
        for (int j = 1; j <= k; ++ j) {
            fc = 1ll * fc * j % mod;
            ans = (ans + 1ll * fc * NTT::S[j] % mod * f[i][j].b) % mod;
        }
        printf("%d\n", ans);
    }

    return 0;
}
