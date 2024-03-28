# include <bits/stdc++.h>

using namespace std;

namespace lyre {
  ifstream  cin("tree.in");
  ofstream cout("tree.out");
  constexpr int nmax(1'200'100);
  constexpr int P(998'244'353);
  default_random_engine rng;
  uniform_int_distribution<uint64_t> randint(0, ULONG_MAX);
  int n, m, ans, R;
  int siz[nmax], fact[nmax];
  bool isleaf[nmax];
  uint64_t h[nmax], sum[nmax];
  vector<int> G[nmax];
  namespace test_case {
    void find(int x, int o) {
      siz[x] = 1;
      auto s(0);
      for (auto y : G[x]) {
        if (y == o) continue;
        find(y, x);
        siz[x] += siz[y];
        s = max(s, siz[y]);
      }
      s = max(s, n - siz[x]);
      if (s <= n / 2) R = x;
    }
    void ins(int x, int y) {
      sum[x] ^= siz[x] * h[siz[x]];
      siz[x] += siz[y], sum[x] += sum[y];
      sum[x] ^= siz[x] * h[siz[x]];
    }
    void era(int x, int y) {
      sum[x] ^= siz[x] * h[siz[x]];
      siz[x] -= siz[y], sum[x] -= sum[y];
      sum[x] ^= siz[x] * h[siz[x]];
    }
    void search0(int x, int o) {
      siz[x] = 1, sum[x] = 0;
      isleaf[x] = true;
      for (auto y : G[x]) {
        if (y == o) continue;
        search0(y, x), isleaf[x] = false;
        ins(x, y);
      }
    }
    void search1(int x, int o) {
      if (o) era(o, x), ins(x, o);
      if (x > n && R <= n && sum[x] == sum[R]) ++ans;
      if (x <= n && R > n && sum[x] == sum[R]) ++ans;
      for (auto y : G[x]) if (y != o) search1(y, x);
      if (o) era(x, o), ins(o, x);
    }
    int calc(int x, int o) {
      auto r(1);
      unordered_map<uint64_t, int> cnt;
      for (auto y : G[x]) {
        if (y == o) continue;
        r = 1l * r * calc(y, x) % P;
        if (!isleaf[y]) ++cnt[sum[y]];
      }
      for (auto [i, y] : cnt)
        r = 1l * r * fact[y] % P;
      return r;
    }
    struct set_union {
      int p[nmax];
      void init(int n) { iota(p + 1, p + n + 1, 1); }
      int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
      void merge(int x, int y) { p[find(y)] = find(x); }
      bool isroot(int x) const { return p[x] == x; }
    } dsu;
    void main() {
      cin >> n, dsu.init(2 * n);
      m = ans = 0, fact[0] = 1;
      for (int i(1); i <= n; ++i) fact[i] = 1l * fact[i - 1] * i % P;
      for (int i(1); i <= n; ++i) h[i] = randint(rng);
      fill(G + 1, G + 2 * n + 1, vector<int>());
      fill(isleaf + 1, isleaf + 2 * n + 1, true);
      fill(siz + 1, siz + 2 * n + 1, 0);
      for (int i(1); i <= n; ++i) {
        int k; cin >> k, m += k;
        for (int j(0); j < k; ++j) {
          int x; cin >> x;
          G[n + i].push_back(x);
          G[x].push_back(n + i);
          dsu.merge(n + i, x);
        }
      }
      if (n == 1) { cout << 1 << '\n'; return; }
      if (m != 2 * (n - 1)) { cout << 0 << '\n'; return; }
      auto cnt(0);
      for (int i(1); i <= 2 * n; ++i) cnt += dsu.isroot(i);
      if (cnt != 2) { cout << 0 << '\n'; return; }
      for (int i(1); i <= 2 * n; ++i) {
        sort(G[i].begin(), G[i].end());
        if (unique(G[i].begin(), G[i].end()) != G[i].end())
        { cout << 0 << '\n'; return; }
      }
      find(1, 0), search0(R, 0);
      for (int i(1); i <= 2 * n; ++i) {
        if (siz[i]) continue;
        search0(i, 0), search1(i, 0);
        cerr << "!!! " << i << ' ' << ans << endl;
        break;
      }
      ans = 1l * ans * calc(R, 0) % P;
      cout << ans << '\n';
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for (int i(0); i < t; ++i)
      test_case::main();
  }
}

int main() { lyre::main(); }