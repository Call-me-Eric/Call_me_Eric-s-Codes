# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("summer.in");
  ofstream cout("summer.out");
  constexpr int P(998'244'353);
  constexpr int pow(int a, int n) {
    int r(1);
    while (n) {
      r = 1l * r * (n & 1 ? a : 1) % P;
      n >>= 1, a = 1l * a * a % P;
    }
    return r;
  }
  constexpr int inv(int const value)
  { return pow(value, P - 2); }
  constexpr int& add(int &a, int const b)
  { return (a += b) >= P ? a -= P : a; }
  namespace subtask0 {
    constexpr size_t N(600);
    vector<int> G[N];
    int f0[N][N * 2], *f[N];
    int n, ans;
    void merge(int u, int v) {
      vector<pair<int, int>> g, h;
      for (int i(-n); i <= n; ++i) if (f[u][i])
        g.emplace_back(i, f[u][i]), f[u][i] = 0;
      for (int i(-n); i <= n; ++i) if (f[v][i])
        h.emplace_back(i, f[v][i]);
      for (auto [i, x] : g) for (auto [j, y] : h) {
        auto const z(1ll * x * y % P);
        if (i >= 0 && j >= 0)
          add(f[u][max(i, j - 1)], z);
        else if (i >= 0 && j < 0)
          add(f[u][i + j >= 0 ? i : j - 1], z);
        else if (i < 0 && j >= 0)
          add(f[u][i + j >= 0 ? j - 1 : i], z);
        else if (i < 0 && j < 0)
          add(f[u][min(i, j - 1)], z);
        else
          assert(false);
      }
    }
    void search(int u, int o, int r) {
      f[u][r] = f[u][-1] = 1;
      for (int v : G[u]) {
        if (v == o) continue;
        search(v, u, r), merge(u, v);
      }
    }
    void main() {
      cin >> n;
      for (int i(1); i <= n; ++i)
        f[i] = f0[i] + N;
      for (int i(1); i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
      }
      for (int r(1); r <= n; ++r) {
        memset(f0, 0x00, sizeof f0);
        search(1, 0, r);
        for (int i(-n); i < 0; ++i)
          add(ans, f[1][i]);
      }
      ans = 1l * (ans + P - 1) * pow(inv(2), n) % P;
      cout << ans << endl;
    }
  }
  namespace subtask2 {
    int n;
    void main() {
      cin >> n;
      auto const tmp(pow(inv(2), n));
      auto const r2(tmp), rm1(tmp);
      auto r0(tmp), ans(0);
      r0 = (r0 + inv(2) * (1l + 2 * (P - tmp)) % P) % P;
      auto r1((1 + 3l * P - r0 - r2 - rm1) % P);
      ans = (ans + 1l * n * r2 % P) % P;
      ans = (ans + r1 - rm1 + P) % P;
      cout << ans << endl;
    }
  }
  namespace subtask4 {
    constexpr size_t N(5'100);
    int n, ans;
    int f[N], sum[N];
    int calc(int const x) {
      auto const len(2 * x + 1);
      fill_n(f + 1, n, 0);
      fill_n(sum + 1, n, 0);
      for (int i(1); i <= n; ++i) {
        if (i - len > 0)
          f[i] = P - sum[i - len - 1];
        f[i] = (f[i] + sum[i - 1]) % P;
        if (i <= x + 1)
          f[i] = (f[i] + 1) % P;
        sum[i] = (sum[i - 1] + f[i]) % P;
      }
      return (sum[n] + P - sum[n - x - 1]) % P;
    }
    void main() {
      cin >> n;
      for (int i(1); i <= n; ++i) {
        ans = (ans + pow(2, n)) % P;
        ans = (ans + P - calc(i)) % P;
      }
      ans = 1l * (ans + P - 1) * pow(inv(2), n) % P;
      cout << ans << endl;
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    switch (t) {
      case 2: subtask2::main(); break;
      case 4: subtask4::main(); break;
      default: subtask0::main(); break;
    }
  }
}

int main() { lyre::main(); }
