#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

int main() {
    static const int maxn = 200010;
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    static vector<int> G[maxn];
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    long long x0 = 0, x1 = 0;
    static bool vis[maxn];
    for (int i = 1; i <= n; i++) {
        if (G[i].size() > 3) {
            printf("-1\n");
            return 0;
        }
        if (G[i].size() == 3) {
            bool flag = true;
            for (int j : G[i])
                flag &= G[j].size() == 1, vis[j] = true;
            vis[i] = true;
            if (!flag) {
                printf("-1\n");
                return 0;
            }
            x1 += 3;
        }
    }
    function<int(int, int)> dfs = [&dfs](const int u, const int fa) {
        int ret = 1;
        vis[u] = true;
        for (int i : G[u])
            if (i != fa)
                ret += dfs(i, u);
        return ret;
    };
    for (int i = 1; i <= n; i++)
        if (!vis[i] && G[i].size() <= 1) {
            int v = dfs(i, 0);
            x0 += (long long)v * (v + 1) >> 1;
        }
    for (int i = 1; i <= n; i++) x1 += !vis[i];
    printf("%d %lld\n", x1 != 0, x1 ? x1 : x0);
    return 0;
}
