#include <cstdio>
using namespace std;

int main() {
    static const long long mod = 998244353;
    static const int maxn = 710;
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    int n, q;
    scanf("%d %d", &n, &q);
    static long long A[maxn][maxn], val[maxn][maxn];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) scanf("%lld", A[i] + j);
    static int p[maxn], r[maxn];
    static auto inv = [](long long x) {
        long long ret = 1, e = mod - 2;
        while (e) {
            if (e & 1) ret = ret * x % mod;
            x = x * x % mod, e >>= 1;
        }
        return ret;
    };
    static auto add = [n](const int a, const int b, const long long x) {
        if (!x) return;
        for (int i = 1; i <= n; i++)
            val[b][i] = (val[b][i] + val[a][i] * x) % mod;
        for (int i = 1; i <= n + 1; i++)
            A[b][i] = (A[b][i] + A[a][i] * x) % mod;
        return;
    };
    auto ins = [n](const int a) {
        val[a][a] = 1;
        for (int i = 1; i <= n; i++)
            if (p[i]) add(i, a, -A[a][p[i]]);
        for (int i = 1; i <= n; i++)
            if (!r[i] && A[a][i]) {
                r[p[a] = i] = a;
                add(a, a, inv(A[a][i]) - 1);
                for (int j = 1; j <= n; j++)
                    if (j != a) add(a, j, -A[j][i]);
                break;
            }
        return;
    };
    auto del = [n](const int a) {
        long long I = inv(val[a][a]);
        for (int i = 1; i <= n; i++)
            if (i != a) add(a, i, -val[i][a] * I % mod);
        for (int i = 1; i <= n; i++) val[a][i] = 0;
        p[a] = r[p[a]] = 0;
        return;
    };
    auto solve = [n](void) {
        bool fN = false, fM = false;
        for (int i = 1; i <= n; i++) {
            bool flag = true;
            for (int j = 1; j <= n; j++) flag &= !A[i][j];
            (A[i][n + 1] ? fN : fM) |= flag;
        }
        if (fN)
            printf("No\n");
        else if (fM)
            printf("Many\n");
        else {
            for (int i = 1; i <= n; i++)
                printf("%lld ", (A[r[i]][n + 1] + mod) % mod);
            printf("\n");
        }
        return;
    };
    for (int i = 1; i <= n; i++) ins(i);
    solve();
    while (q--) {
        int z;
        scanf("%d", &z), del(z);
        for (int i = 1; i <= n + 1; i++) scanf("%lld", A[z] + i);
        ins(z), solve();
    }
    return 0;
}
