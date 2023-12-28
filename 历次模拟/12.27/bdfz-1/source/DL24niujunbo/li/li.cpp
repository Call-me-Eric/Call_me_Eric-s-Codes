# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("li.in");
  ofstream cout("li.out");
  constexpr size_t N(200'100);
  vector<pair<int, int>> G[N];
  vector<int> H[N];
  bool vis[N];
  int n, m, cnt;
  long k, b, ans;
  void search0(int x) {
    vis[x] = true;
    for (auto [y, z] : G[x])
      if (!vis[y]) search0(y);
    for (auto [y0, z0] : G[x]) {
      for (auto [y1, z1] : G[x]) {
        if (z0 == z1) continue;
        H[z0].push_back(z1);
      }
    }
  }
  void search1(int x, vector<int> &s) {
    vis[x] = true, s.push_back(x);
    for (auto y : H[x])
      if (!vis[y]) search1(y, s);
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, b += n;
    for (int i(1); i <= m; ++i) {
      int x, y;
      cin >> x >> y;
      G[x].emplace_back(y, i);
      G[y].emplace_back(x, i);
    }
    for (int i(1); i <= n; ++i) {
      if (G[i].size() > 3u) {
        cout << -1 << endl;
        return;
      }
    }
    for (int i(1); i <= n; ++i)
      if (!vis[i]) search0(i);
    for (int i(1); i <= m; ++i) {
      sort(H[i].begin(), H[i].end());
      auto ed(unique(H[i].begin(), H[i].end()));
      H[i].erase(ed, H[i].end());
      if (H[i].size() > 3u) {
        cout << -1 << endl;
        return;
      }
    }
    memset(vis, false, sizeof vis);
    for (int i(1); i <= m; ++i) {
      if (vis[i]) continue;
      vector<int> u;
      search1(i, u);
      int cnt[]{ 0, 0, 0 };
      for (auto const &j : u) {
        if (H[j].size() > 2u) {
          cout << -1 << endl;
          return;
        }
        cnt[H[j].size()] += 1;
      }
      if (cnt[0]) b += 1;
      else if (cnt[1]) b += 1l * u.size() * (u.size() + 1) / 2;
      else k += cnt[2];
    }
    if (k) cout << 1 << ' ' << k << endl;
    else cout << 0 << ' ' << b << endl;
  }
}

int main() { lyre::main(); }