#include <cmath>
#include <cstdio>
#include <vector>
#include <chrono>
#include <random>
const int N = 2e5 + 10; std::vector<int> con[N]; int deg[N];
struct DSU
{
    int f[N];
    void init(int n) { for (int i = 1; i <= n; ++i) f[i] = i; }
    int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]); }
    void merge(int x, int y) { f[getf(x)] = getf(y); }
}dsu;
int main()
{
    freopen("li.in", "r", stdin); freopen("li.out", "w", stdout);
    int n, m, s = 0; scanf("%d%d", &n, &m); long long ans = 0; dsu.init(n);
    for (int i = 1, x, y; i <= m; ++i) scanf("%d%d", &x, &y), ++deg[x], ++deg[y], dsu.merge(x, y);
    for (int i = 1; i <= n; ++i) con[dsu.getf(i)].push_back(i);
    for (int i = 1; i <= n; ++i)
    {
        if (con[i].empty()) continue;
        int mx = 0;
        for (auto u : con[i]) mx = std::max(mx, deg[u]);
        if (mx > 3) return puts("-1"), 0;
        if (mx == 3 && con[i].size() > 1) return puts("-1"), 0;
        if (mx == 3 && !s) ans = 3, s = 1;
        else if (mx == 3) ans += 3;
        if (mx == 2)
        {
            int flg = 0;
            for (auto u : con[i]) flg |= (deg[u] == 1);
            if (flg && !s) ans += 1ll * con[i].size() * (con[i].size() + 1) / 2;
            if (!flg && !s) s = 1, ans = con[i].size();
            else if (!flg) ans += con[i].size();
        }
        if (!mx && !s) ++ans;
        if (mx == 1 && !s) ans += 3;
    }
    printf("%d %lld\n", s, ans); return 0;
}