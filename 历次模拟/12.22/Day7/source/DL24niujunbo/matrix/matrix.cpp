# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("matrix.in");
  ofstream cout("matrix.out");
  constexpr int N(1'005), V(25);
  int n, m;
  class bitset {
    uint64_t v[(N >> 6) + 1];
    public:
    constexpr bitset() : v() {}
    constexpr bool operator[](int i) const { return v[i >> 6] >> (i & 0x3f) & 1; }
    constexpr void set(int i) { v[i >> 6] |= 1ul << (i & 0x3f); }
    constexpr bool operator*(bitset const &b) const {
      bool res(0);
      for (auto i(v), j(b.v); i != v + (N >> 6) + 1;)
        res ^= __builtin_parityll(*i++ & *j++);
      return res;
    }
  };
  class matrix {
    bitset col[N], row[N];
    public:
    constexpr matrix() : col(), row() {}
    constexpr void set(int i, int j) { row[i].set(j), col[j].set(i); }
    constexpr bool operator()(int i, int j) const { return row[i][j]; }
    inline matrix operator*(matrix const &b) const {
      matrix r;
      for (int i(0); i < n; ++i) {
        for (int j(0); j < n; ++j) {
          if (row[i] * b.col[j])
            r.set(i, j);
        }
      }
      return r;
    }
    inline bitset operator*(bitset const &b) const {
      bitset r;
      for (int i(0); i < n; ++i)
        if (row[i] * b) r.set(i);
      return r;
    }
    inline bool operator==(matrix const &b) const {
      for (int i(0); i < n; ++i) {
        for (int j(0); j < n; ++j) {
          if (row[i][j] != b(i, j))
            return false;
        }
      }
      return true;
    }
  } mat[V + 1];
  bitset x;
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i(0); i < n; ++i) {
      for (int j(0); j < n; ++j) {
        char tmp; cin >> tmp;
        if (tmp == '1') mat[0].set(i, j);
      }
    }
    for (int i(0); i < n; ++i) {
      char tmp; cin >> tmp;
      if (tmp == '1') x.set(i);
    }
    for (int i(1); i <= V; ++i)
      mat[i] = mat[i - 1] * mat[i - 1];
    cin >> m;
    for (int i(0); i < m; ++i) {
      int k; cin >> k;
      auto y(x);
      while (k >= 1 << (V + 1))
        y = mat[V] * y, k -= 1 << V;
      for (int i(V); ~i; --i)
        if (k >> i & 1) y = mat[i] * y;
      for (int j(0); j < n; ++j)
        cout << y[j];
      cout << '\n';
    }
  }
}

int main() { lyre::main(); }
