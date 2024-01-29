# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("hard.in");
  ofstream cout("hard.out");
  constexpr size_t N(2'100);
  constexpr size_t M(100'100);
  constexpr int P(1'000'000'007);
  constexpr int pow(int a, int n) {
    auto r(1);
    while (n) {
      r = 1l * r * (n & 1 ? a : 1) % P;
      n >>= 1, a = 1l * a * a % P;
    }
    return r;
  }
  constexpr int inv(int const a)
  { return pow(a, P - 2); }
  int n, m; long sum;
  int a[N], f[M];
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i(1); i <= n; ++i) {
      cin >> a[i], sum += a[i];
      m = max(m, a[i]);
    }
    f[1] = (sum - 1) * (sum - 1) % P * inv(sum) % P;
    f[2] = (2l * f[1] - 1) % P;
    for (int i(2); i < m; ++i) {
      f[i + 1] = 2l * f[i] % P;
      f[i + 1] = (f[i + 1] + P - f[i - 1]) % P;
      f[i + 1] = (f[i + 1] + P - (sum - 1) * inv(sum - i) % P) % P;
    }
    auto ans(0);
    for (int i(1); i <= n; ++i)
      ans = (ans + f[a[i]]) % P;
    cout << ans << endl;
  }
}

int main() { lyre::main(); }
