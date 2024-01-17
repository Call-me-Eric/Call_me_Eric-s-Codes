# include <iostream>
# include <fstream>
# include <algorithm>

namespace lyre {
  using namespace std;
  ifstream  cin("city.in");
  ofstream cout("city.out");
  constexpr size_t N(110);
  constexpr int P(22'222'223);
  int n, m, a[N], b[N];
  inline int calc(int s, int x) {
    auto r0(1), r1(1);
    for (int i(0); i < n; ++i) {
      auto u0(b[x]), u1(b[x] - 1);
      if (s >> i & 1) {
        u0 = min(u0, a[i] - 1);
        u1 = min(u1, a[i] - 1);
      } else {
        u0 = min(u0, a[i]);
        u1 = min(u1, a[i]);
      }
      r0 = 1l * r0 * (u0 + 1) % P;
      r1 = 1l * r1 * (u1 + 1) % P;
    }
    return (r0 - r1 + P) % P;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i(0); i < n; ++i) cin >> a[i];
    for (int i(0); i < m; ++i) cin >> b[i];
    auto ans(0);
    for (int i(0); i != 1 << n; ++i) {
      auto r(1);
      for (int j(0); j < m; ++j)
        r = 1l * r * calc(i, j) % P;
      auto sgn(__builtin_popcount(i) & 1 ? P - 1 : 1);
      ans = (ans + 1l * sgn * r % P) % P;
    }
    cout << ans << endl;
  }
}

int main() { lyre::main(); }