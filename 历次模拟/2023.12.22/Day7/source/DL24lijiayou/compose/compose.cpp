# include <bits/stdc++.h>

using namespace std;

namespace kh {
  ifstream cin("compose.in");
  ofstream cout("compose.out");
  constexpr int N(100'000);
  constexpr int Q(100'000);
  constexpr int K(12);
  int n, k, q, m;
  int a[K][N + 1];
  int p[N + 1][K];
  bitset<1 << K> s[K + Q];
  inline int get(int const x, int const y) {
    int t((1 << k) - 1);
    for (int i(0); i != k; ++i)
      if (!s[x].test(t ^= 1 << p[y][i]))
        return a[p[y][i]][y];
    __builtin_unreachable();
  }
  void main() {
    cin >> n >> k >> q, m = k;
    for (int i(0); i != k; ++i)
      for (int j(1); j <= n; ++j)
        cin >> a[i][j];
    for (int i(1); i <= n; ++i) {
      auto const cmp =
        [i] (int const j, int const k)
        { return a[j][i] < a[k][i]; };
      iota(p[i], p[i] + k, 0);
      sort(p[i], p[i] + k, cmp);
    }
    for (int i(0); i != k; ++i)
      for (int j(0); j != 1 << k; ++j)
        s[i].set(j, j >> i & 1);
    for (int i(1); i <= q; ++i) {
      int o, a, b;
      cin >> o >> a >> b;
      switch (o) {
        case 1:
          s[m++] = s[--a] | s[--b];
          break;
        case 2:
          s[m++] = s[--a] & s[--b];
          break;
        case 3:
          cout << get(--a, b) << endl;
          break;
      }
    }
  }
}

int main() { kh::main(); }
