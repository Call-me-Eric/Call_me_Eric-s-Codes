# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("grid.in");
  ofstream cout("grid.out");
  constexpr size_t N(250);
  constexpr int P(998244353);
  int n, m, q, a[N][N];
  int f[N][N][N], g[N][N][N];
  constexpr int dx[]{ +1, -1, 0, 0 };
  constexpr int dy[]{ 0, 0, +1, -1 };
  inline bool exist(int const x, int const y)
  { return x >= 1 && x <= n && y >= 1 && y <= n; }
  inline void solve() {
    memset(f, 0x00, sizeof f);
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j)
        f[i][j][m] = 1;
    }
    for (int t(m); t > 1; --t) {
      for (int i(1); i <= n; ++i) {
        for (int j(1); j <= n; ++j) {
          f[i][j][t - 1] = (f[i][j][t - 1] + f[i][j][t]) % P;
          for (int k(0); k < 4; ++k) {
            auto const x(i + dx[k]);
            auto const y(j + dy[k]);
            if (!exist(x, y)) continue;
            if (t != a[x][y] + 1) continue;
            f[x][y][t - 1] = (f[x][y][t - 1] + f[i][j][t]) % P;
          }
        }
      }
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> dst;
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        cin >> a[i][j];
        dst.push_back(a[i][j]);
      }
    }
    sort(dst.begin(), dst.end());
    dst.erase(unique(dst.begin(), dst.end()), dst.end());
    m = dst.size() + 1;
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        auto const k(lower_bound(dst.begin(), dst.end(), a[i][j]));
        a[i][j] = distance(dst.begin(), k) + 1;
      }
    }
    cin >> q;
    solve();
    while (q--) {
      auto x(0), y(0), z(0);
      cin >> x >> y;
      swap(a[x][y], z);
      solve();
      swap(a[x][y], z);
      for (int i(1); i <= n; ++i)
        for (int j(1); j <= n; ++j)
          z = (z + f[i][j][1]) % P;
      cout << z << "\n";
    }
  }
}

int main() { lyre::main(); }


# if false
# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("grid.in");
//  ofstream cout("grid.out");
  constexpr size_t N(250);
  constexpr int P(998244353);
  constexpr int dx[]{ +1, -1, 0, 0 };
  constexpr int dy[]{ 0, 0, +1, -1 };
  int n, m, q, a[N][N];
  inline bool exist(int const x, int const y)
  { return x >= 1 && x <= n && y >= 1 && y <= n; }
  struct vertex {
    vector<pair<int, int>> t;
    vector<int> val, deg;
    vertex() : t(), val(), deg() {}
    inline int find(int const x) {
      for (size_t i(0); i < t.size(); ++i)
        if (t[i].first <= x && x <= t[i].second)
          return i;
      assert(false);
      return 0;
    }
    inline bool add(int const x, int const y) {
      val[x] = (val[x] + y) % P;
      if (!--deg[x]) return true;
      return false;
    }
    inline void init(int const x, int const y) {
      t.clear(), val.clear(), deg.clear();
      vector<int> dst;
      dst.push_back(a[x][y]);
      for (int k(0); k < 4; ++k) {
        auto const i(x + dx[k]);
        auto const j(y + dy[k]);
        if (!exist(i, j)) continue;
        dst.push_back(a[i][j]);
      }
      sort(dst.begin(), dst.end());
      dst.erase(unique(dst.begin(), dst.end()), dst.end());
      t.emplace_back(0, dst.front());
      for (size_t i(0); i + 1 < dst.size(); ++i)
        t.emplace_back(dst[i] + 1, dst[i + 1]);
      t.emplace_back(dst.back() + 1, m + 2);
      val.resize(t.size(), 0);
      val.back() = 1;
      deg.resize(t.size(), 1);
      deg.back() = 0;
    }
  } f[N][N];

  inline int solve() {
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j)
        f[i][j].init(i, j);
    }
    
    for (int x(1); x <= n; ++x) {
      for (int y(1); y <= n; ++y) {
        auto const u(f[x][y].find(a[x][y]));
        for (int k(0); k < 4; ++k) {
          auto const i(x + dx[k]);
          auto const j(y + dy[k]);
          if (!exist(i, j)) continue;
          auto const v(f[i][j].find(a[x][y] + 1));
          if (f[x][y].t[u].second + 1 != f[i][j].t[v].first)
            continue;
          if (a[x][y] == m + 1)
            continue;
          cerr << "ok, " << i << ' ' << j << ' ' << x << ' ' << y << endl;
          cerr << f[x][y].t[u].second << ' ' << f[i][j].t[v].first << endl;
          ++f[x][y].deg[u];
        }
      }
    }
    
    for (int i(1); i <= n; ++i)
      for (int j(1);j <= n; ++j) {
        cout << "f: " << i << ' ' << j << endl;
        for (int k(0); k < f[i][j].t.size(); ++k) {
          cout << f[i][j].t[k].first << ' ' << f[i][j].t[k].second << ' ';
          cout << f[i][j].deg[k] << endl;
        }
        cout << "..............." << endl;
      }
    
    queue<tuple<int, int, int>> q;
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        for (size_t k(0); k < f[i][j].t.size(); ++k) {
          if (!f[i][j].deg[k])
            q.emplace(i, j, k);
        }
      }
    }
    
    while (!q.empty()) {
      auto const x(get<0>(q.front()));
      auto const y(get<1>(q.front()));
      auto const z(get<2>(q.front()));
      q.pop();
      cerr << x << ' ' << y << ' ' << z << endl;
      assert(f[x][y].deg[z - 1]);
      if (z && f[x][y].add(z - 1, f[x][y].val[z]))
        q.emplace(x, y, z - 1);
      for (int k(0); k < 4; ++k) {
        auto const i(x + dx[k]);
        auto const j(y + dy[k]);
        if (!exist(i, j)) continue;
        auto const u(f[x][y].find(a[i][j] - 1));
        if (z != u) continue;
        auto const v(f[i][j].find(a[i][j]));
        if (f[i][j].t[v].second + 1 != f[x][y].t[u].first)
          continue;
        if (a[i][j] == m + 1)
          continue;
        assert(!f[i][j].deg[v]);
        if (f[i][j].add(v, f[x][y].val[u])) {
          q.emplace(i, j, v);
          cerr << "empalce: " << i << ' ' << j << ' ' << v << endl;
        }
      }
    }
    int ans(0);
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= m; ++j)
        ans = (ans + f[i][j].val.front()) % P;
    }
    return ans;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> dst;
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        cin >> a[i][j];
        dst.push_back(a[i][j]);
      }
    }
    sort(dst.begin(), dst.end());
    dst.erase(unique(dst.begin(), dst.end()), dst.end());
    m = dst.size() + 1;
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        auto const k(lower_bound(dst.begin(), dst.end(), a[i][j]));
        a[i][j] = distance(dst.begin(), k) + 1;
      }
    }
    cin >> q;
    q = 1;
    while (q--) {
      auto x(0), y(0), z(m + 1);
      cin >> x >> y;
      swap(a[x][y], z);
      cout << solve() << "\n";
      swap(a[x][y], z);
      cout.flush();
    }
  }
}

int main() { lyre::main(); }
# endif
