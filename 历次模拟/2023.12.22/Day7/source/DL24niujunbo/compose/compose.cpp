# include <bits/stdc++.h> 

namespace lyre {
  using namespace std;
  ifstream  cin("compose.in");
  ofstream cout("compose.out");
  constexpr size_t N(100'100), K(14);
  constexpr int inf(INT_MAX / 2);
  bitset<1 << K> s[N];
  int n, m, k, q;
  int a[K][N];
  inline void ins0(int x, int y)
  { s[m++] = s[x] | s[y]; }
  inline void ins1(int x, int y)
  { s[m++] = s[x] & s[y]; }
  inline int at(int x, int y) {
    auto res(0);
    for (int i(0); i < k; ++i) {
      auto t(0);
      for (int j(0); j < k; ++j)
        t |= (a[j][y] >= a[i][y]) << j;
      if (s[x].test(t))
        res = max(res, a[i][y]);
    }
    return res;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> q, m = k;
    for (int i(0); i < k; ++i) {
      for (int j(0); j < n; ++j)
        cin >> a[i][j];
    }
    for (int i(0); i < k; ++i) {
      for (int j(0); j != 1 << k; ++j) {
        if (j >> i & 1) s[i].set(j);
      }
    }
    for (int i(0); i < q; ++i) {
      int opt, x, y;
      cin >> opt >> x >> y;
      --x, --y;
      switch (opt) {
        case 1: ins0(x, y); break;
        case 2: ins1(x, y); break;
        case 3: cout << at(x, y) << '\n'; break;
      }
    }
  }
}

int main() { lyre::main(); }
