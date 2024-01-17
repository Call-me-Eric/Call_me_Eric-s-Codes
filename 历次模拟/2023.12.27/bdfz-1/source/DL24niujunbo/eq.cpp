# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("eq.in");
  ofstream cout("eq.out");
  constexpr size_t N(750);
  constexpr int P(998'244'353);
  constexpr int pow(int a, int n) {
    auto r(1);
    while (n) {
      r = 1l * r * (n & 1 ? a : 1) % P;
      n >>= 1, a = 1l * a * a % P;
    }
    return r;
  }
  constexpr int inv(int a)
  { return pow(a, P - 2); }
  int n, q, a[N][N];
  void solve() {
    static decltype(a) a0;
    memcpy(a0, a, sizeof a0);
    auto row(0), col(0);
    for (; col < n; ++col) {
      auto ptr(row);
      for (int i(row); i < n; ++i) {
        if (a[i][col] > a[ptr][col])
          ptr = i;
      }
      if (!a[ptr][col]) continue;
      swap(a[ptr], a[row]);
      for (int i(n); i >= col; --i)
        a[row][i] = 1l * a[row][i] * inv(a[row][col]) % P;
      for (int i(row + 1); i < n; ++i) {
        if (!a[i][col]) continue;
        for (int j(n); j >= col; --j)
          a[i][j] = (a[i][j] + P - 1l * a[row][j] * a[i][col] % P) % P;
      }
      row += 1;
    }
    for (int i(n - 1); i >= 0; --i) {
      for (int j(i + 1); j < n; ++j)
        a[i][n] = (a[i][n] + P - 1l * a[i][j] * a[j][n] % P) % P;
    }
    if (row < n) {
      auto flag(false);
      for (int i(row); !flag && i < n; ++i)
        if (a[i][n]) cout << "NO\n", flag = true;
      if (!flag) cout << "Many\n";
    } else {
      for (int i(0); i < n; ++i)
        cout << a[i][n] << " \n"[i == n - 1];
    }
    memcpy(a, a0, sizeof a);
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i(0); i < n; ++i) {
      for (int j(0); j <= n; ++j)
        cin >> a[i][j];
    }
    solve();
    for (int i(1), z; i <= q; ++i) {
      cin >> z;
      for (int j(0); j <= n; ++j)
        cin >> a[z - 1][j];
      solve();
    }
  }
}

int main() { lyre::main(); }