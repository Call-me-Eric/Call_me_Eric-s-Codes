# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("strawberry.in");
  ofstream cout("strawberry.out");
  constexpr size_t N(1'100);
  constexpr size_t V(10'100);
  template <class T> constexpr T& cmax(T &a, T const b)
    { return a = max(a, b); }
  int n, k, v, p[N], q[N];
  int f[N][V * 2];
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k, v = k;
    for (int i(1); i < n; ++i) {
      cin >> p[i] >> q[i];
      cmax(v, p[i] + q[i]);
    }
    iota(f[1], f[1] + k, 0);
    for (int i(1); i < n; ++i) {
      auto s(0);
      for (int j(0); j <= v; ++j) {
        if (j < p[i]) {
          cmax(f[i + 1][j + q[i]], f[i][j] + q[i]);
          cmax(s, f[i][j]);
        } else if (j < p[i] + q[i]) {
          cmax(f[i + 1][j - p[i]], f[i][j]);
        } else {
          cmax(f[i + 1][j], f[i][j]);
        }
      }
      for (int j(0); j < q[i]; ++j)
        cmax(f[i + 1][j], s + j);
    }
    cout << *max_element(f[n], f[n] + v + 1) << endl;
  }
}

int main() { lyre::main(); }
