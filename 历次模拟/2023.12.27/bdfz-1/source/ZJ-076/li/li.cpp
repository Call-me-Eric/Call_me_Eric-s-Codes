#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
using ll = long long;
int n,m,cnt;vector<int> v[N];
bool vis[N];
ll ans;int tt;
void dfs(int pos) { ++tt;vis[pos] = 1;for (auto &i : v[pos]) if (!vis[i]) dfs(i); }
int main ()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1;i <= m;i++) { int t1,t2;cin >> t1 >> t2;v[t1].push_back(t2);v[t2].push_back(t1); }
    for (int i = 1;i <= n;i++)
    {
        if (v[i].size() > 3) {cout << -1 << endl;return 0;}
        if (v[i].size() == 3)
        {
            vis[i] = 1;
            for (auto &j : v[i]) if (v[j].size() != 1) {cout << -1 << endl;return 0;} else vis[j] = 1;
            cnt += 3;
        }
    }
    for (int i = 1;i <= n;i++) if (v[i].size() == 1 && !vis[i]) {tt = 0;dfs(i);ans += tt * ll(tt + 1) / 2;}
    for (int i = 1;i <= n;i++) if (v[i].size() == 2 && !vis[i]) {tt = 0;dfs(i);cnt += tt;} else if (v[i].empty()) ++ans;
    if (cnt) cout << 1 << ' ' << cnt << endl;else cout << 0 << ' ' << ans << endl;
    return 0;
}