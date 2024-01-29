#include <cstdio>
#include <algorithm>
const int N = 710, mod = 998244353; typedef long long ll; int a[N][N], b[N][N];
inline int ksm(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1) ret = (ll)ret * a % mod;
        a = (ll)a * a % mod; b >>= 1;
    }
    return ret;
}
void solve(int n)
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j) a[i][j] = b[i][j];
    int r = 1;
    for (int i = 1, o; i <= n; ++i)
    {
        o = r;
        for (int j = r + 1; j <= n; ++j) if (a[o][i] < a[j][i]) o = j;
        std::swap(a[o], a[r]); if (!a[r][i]) continue;
        int t = ksm(a[r][i], mod - 2);
        for (int j = 1; j <= n + 1; ++j) a[r][j] = (ll)a[r][j] * t % mod;
        for (int j = r + 1; j <= n; ++j)
        {
            t = a[j][i];
            for (int k = i; k <= n + 1; ++k) a[j][k] = (a[j][k] + mod - (ll)t * a[r][k] % mod) % mod;
        }
        ++r;
    }
    for (int i = n; i; --i)
    {
        if (!a[i][i]) continue;
        for (int j = i - 1; j; --j)
        {
            int t = (ll)a[j][i] * ksm(a[i][i], mod - 2) % mod;
            for (int k = 1; k <= n + 1; ++k) a[j][k] = (a[j][k] + mod - (ll)t * a[i][k] % mod) % mod;
        }
    }
    int flg1 = 0, flg2 = 0;
    for (int i = r; i <= n; ++i)
    {
        if (!a[i][n + 1]) flg1 = 1;
        if (a[i][n + 1]) flg2 = 1;
    }
    if (!flg1 && !flg2)
    {
        for (int i = 1; i <= n; ++i) printf("%lld%c", (ll)a[i][n + 1] * ksm(a[i][i], mod - 2) % mod, i == n ? '\n' : ' ');
        return ;
    }
    if (flg2) return puts("No"), void();
    if (flg1) return puts("Many"), void();
}
int main()
{
    freopen("eq.in", "r", stdin); freopen("eq.out", "w", stdout);
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j) scanf("%d", &b[i][j]);
    solve(n);
    for (int i = 1; i <= q; ++i)
    {
        int z; scanf("%d", &z);
        for (int j = 1; j <= n + 1; ++j) scanf("%d", &b[z][j]);
        solve(n);
    }
    return 0;
}