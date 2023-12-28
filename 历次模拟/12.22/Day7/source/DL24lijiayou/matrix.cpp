# include <bits/stdc++.h>

using namespace std;

namespace kh {
  ifstream cin("matrix.in");
  ofstream cout("matrix.out");
  inline char getgraph() { char c; cin >> c; return c; }
  constexpr int N(1'000);
  constexpr int M(100);
  constexpr int K(1'000'000'000);
  template <int M>
    class matrix {
      bitset<N> c[M];
      public:
      constexpr matrix() = default;
      constexpr matrix(matrix&&) = default;
      constexpr matrix(matrix const&) = default;
      constexpr matrix& operator=(matrix&&) = default;
      constexpr matrix& operator=(matrix const&) = default;
      constexpr auto& operator[](int const x) { return c[x]; }
      constexpr auto const& operator[](int const x) const { return c[x]; }
      friend constexpr matrix operator*(matrix<N> const a, matrix const b) {
        matrix c;
        for (int i(0); i != M; ++i)
          for (int j(b[i]._Find_first()); j != N; j = b[i]._Find_next(j))
            c[i] ^= a[j];
        return c;
      }
    };
  int n, m, k;
  matrix<N> a;
  matrix<1> b;
  matrix<N> pow[__lg(K) + 1];
  void main() {
    cin >> n;
    for (int i(0); i != n; ++i)
      for (int j(0); j != n; ++j)
        a[j].set(i, getgraph() - '0');
    pow[0] = a;
    for (int i(1); K >> i; ++i)
      pow[i] = pow[i - 1] * pow[i - 1];
    for (int i(0); i != n; ++i)
      kh::b[0].set(i, getgraph() - '0');
    cin >> m;
    for (int i(0); i != m; ++i) {
      cin >> k;
      auto r(b);
      while (k)
        r = pow[__builtin_ctz(k)] * r, k &= k - 1;
      for (int j(0); j != n; ++j)
        cout << r[0].test(j) << (j == n - 1 ? "\n" : "");
    }
  }
}

int main() { kh::main(); }
