# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("distanced.in");
  ofstream cout("distanced.out");
  constexpr size_t N(2100);
  constexpr long long inf(LLONG_MAX / 4);
  using pair = pair<int, long long>;
  pair v[N];
  int n, t;
  long long f[N][N], ans[N];
  struct segment_tree {
    long long val[N * 4];
    void build(int u, int l, int r) {
      val[u] = -inf;
      if (l == r) return;
      auto const mid((l + r) / 2);
      build(u << 1, l, mid);
      build(u << 1 | 1, mid + 1, r);
    }
    void set(int u, int l, int r, int x, long long y) {
      if (l == r) {
        val[u] = y;
        return;
      }
      auto const mid((l + r) / 2);
      if (x <= mid) set(u << 1, l, mid, x, y);
      else set(u << 1 | 1, mid + 1, r, x, y);
      val[u] = max(val[u << 1], val[u << 1 | 1]);
    }
    long long qmax(int u, int l, int r, int x, int y) {
      if (l == x && r == y)
        return val[u];
      auto const mid((l + r) / 2);
      if (y <= mid)
        return qmax(u << 1, l, mid, x, y);
      if (x > mid)
        return qmax(u << 1 | 1, mid + 1, r, x, y);
      return max(qmax(u << 1, l, mid, x, mid),
                 qmax(u << 1 | 1, mid + 1, r, mid + 1, y));
    }
  } seg[N];
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> t;
    for (int i(1); i <= n; ++i)
      cin >> v[i].first;
    for (int i(1); i <= n; ++i)
      cin >> v[i].second;
    sort(v + 1, v + n + 1, [] (pair x, pair y)
    { return x.first < y.first; });
    for (int i(1); i <= n; ++i)
      seg[i].build(1, 1, n);
    memset(f, 0xcf, sizeof f);
    memset(ans, 0xcf, sizeof ans);
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        if (j == 1)
          f[i][j] = max(f[i][j], v[i].second);
        auto const x(make_pair(v[i].first - t, 0ll));
        auto const y(lower_bound(v + 1, v + i, x) - v);
        if (y < i)
          f[i][j] = max(f[i][j], seg[j].qmax(1, 1, n, y, i - 1) + v[i].second);
        if (j > 1 && y > 1)
          f[i][j] = max(f[i][j], seg[j - 1].qmax(1, 1, n, 1, y - 1) + v[i].second);
        ans[j] = max(ans[j], f[i][j]);
        seg[j].set(1, 1, n, i, f[i][j]);
      }
    }
    for (int i(1); i <= n; ++i) {
      if (i > 1) ans[i] = max(ans[i], ans[i - 1]);
      cout << ans[i] << " \n"[i == n];
    }
  }
}

int main() { lyre::main(); }
