#include <bits/stdc++.h>
using namespace std;
int read()
{
    int sum = 0, ne = 1;
    char ch = getchar();
    for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
    if (ch == '-') ne = -1, ch = getchar();
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        sum = (sum << 1) + (sum << 3) + (ch ^ 48);
    return sum * ne;
}
const int maxn = 2e5 + 5;
vector<pair<int, int>> edge[maxn];
bool flag[maxn];
vector<pair<int, int>> ty;
void dfs(int x, int lst, int fa)
{
    for (auto i : edge[x])
        if (i.first != fa)
        {
            if (lst) ty.emplace_back(lst, i.second);
            if (!flag[i.first])
                flag[i.first] = 1, dfs(i.first, i.second, x);
        }
}
pair<vector<int>, vector<pair<int, int>>> L(vector<int> x, vector<pair<int, int>> y)
{
    vector<int> tx;
    ty.clear();
    for (int i = 1; i <= x.size(); i++) edge[i].clear(), flag[i] = 0;
    for (int i = 1; i <= y.size(); i++)
        tx.emplace_back(i), edge[y[i - 1].second].emplace_back(y[i - 1].first, i), edge[y[i - 1].first].emplace_back(y[i - 1].second, i);
    for (int i = 1; i <= x.size(); i++)
        if (!flag[i])
            dfs(i, 0, 0);
    return make_pair(tx, ty);
}
signed main()
{
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    int n = read(), m = read();
    vector<int> v;
    for (int i = 1; i <= n; i++) v.emplace_back(i);
    vector<pair<int, int>> e;
    for (int i = 1; i <= m; i++)
    {
        int u = read(), v = read();
        e.emplace_back(u, v);
    }
    int cnt = 0;
    int lst = n;
    bool flag = 0;
    long long ans = 0;
    while (cnt <= 10)
    {
        auto tmp = L(v, e);
        ans += v.size();
        v = tmp.first, e = tmp.second;
        if (v.size() > lst)
            return puts("-1"), 0;
        else if (v.size() < lst)
        {
            flag = 1;
            break;
        }
        cnt++;
    }
    if (flag)
    {
        while (v.size())
        {
            ans += v.size();
            auto tmp = L(v, e);
            v = tmp.first, e = tmp.second;
        }
        printf("0 %lld", ans);
    }
    else printf("1 %d", n);
    return 0;
}