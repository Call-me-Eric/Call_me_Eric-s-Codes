# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("color.in");
  ofstream cout("color.out");
  constexpr size_t N(2000);
  constexpr int P(998244353);
  vector<int> G[N];
  int n, m, k, c[N];
  int f[N][N], g[N];
  void solve(int const u, int const o) {
    for (auto const v : G[u])
      if (v != o) solve(v, u);
    for (int i(0); i <= m; ++i) {
      if (c[u] && c[u] != i) continue;
      f[u][i] = i || m < k;
      for (auto const v : G[u]) {
        if (v == o) continue;
        auto sum(0ll);
        if (i) {
          sum = (sum + g[v] + (P - f[v][i])) % P;
          sum = (sum + 1ll * f[v][0] * (k - m)) % P;
        } else {
          sum = (sum + g[v]) % P;
          sum = (sum + 1ll * f[v][0] * (k - m - 1)) % P;
        }
        f[u][i] = f[u][i] * sum % P;
      }
    }
    g[u] = accumulate(f[u] + 1, f[u] + m + 1, 0ll) % P;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    vector<int> dst;
    for (int i(1); i <= n; ++i) {
      cin >> c[i];
      if (c[i]) dst.push_back(c[i]);
    }
    sort(dst.begin(), dst.end());
    dst.erase(unique(dst.begin(), dst.end()), dst.end());
    m = dst.size();
    for (int i(1); i <= n; ++i) {
      if (!c[i]) continue;
      auto const j(lower_bound(dst.begin(), dst.end(), c[i]));
      c[i] = distance(dst.begin(), j) + 1;
    }
    for (int i(1); i < n; ++i) {
      int u, v; cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    solve(1, 0);
    auto ans(1ll * f[1][0] * (k - m) % P);
    ans = (ans + accumulate(f[1] + 1, f[1] + m + 1, 0ll) % P) % P;
    cout << ans << endl;
  }
}

int main() { lyre::main(); }
