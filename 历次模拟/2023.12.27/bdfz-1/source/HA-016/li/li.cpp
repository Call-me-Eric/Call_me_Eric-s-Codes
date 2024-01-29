#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;

int n, m, du[N], ans[2];
vector<int> vec, g[N];
bool pd = false;
bool vis[N];

void dfs(int x) {
    vis[x] = true; vec.push_back(x);
    for (auto y : g[x]) {
        if (vis[y]) continue;
        dfs(y);
    }
}

void work(int x) {
    vec.clear(); dfs(x);
    int cnt[4]; memset(cnt, 0, sizeof(cnt));
    int tmp = vec.size();
    for (auto y : vec) cnt[du[y]]++;
    if (cnt[3] >= 2) puts("-1"), exit(0);
    else if (cnt[3] == 1) {
        if (cnt[1] == 3 && cnt[2] == 0 && cnt[0] == 0) pd = true, ans[1] += 3;
        else puts("-1"), exit(0);
    }else if (cnt[1] == 0 && cnt[2] != 0) {
        pd = true; ans[1] += tmp;
    }else ans[0] += (tmp + 1) * tmp / 2;
}

signed main() {
     freopen("li.in", "r", stdin);
     freopen("li.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("%lld%lld", &x, &y);
        g[x].push_back(y); g[y].push_back(x);
        du[x]++; du[y]++;
    }
    for (int i = 1; i <= n; ++i)
        if (du[i] > 3) return puts("-1"), 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) work(i);
    printf("%lld %lld\n", (int)pd, ans[pd]);
    return 0;
}
