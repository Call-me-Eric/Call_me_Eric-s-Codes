# include <bits/stdc++.h>

using namespace std;

namespace kh {
  ifstream cin("hard.in");
  ofstream cout("hard.out");
  constexpr int P(1'000'000'007);
  constexpr int inv(int x) {
    int r(1);
    while (x != 1)
      r = 1l * r * -(P / x) % P, x = P % x;
    return r;
  }
  constexpr int N(2'000);
  constexpr int A(100'000);
  int n, s, m;
  int a[N + 1];
  int f[A + 1];
  int ans;
  void main() {
    cin >> n, f[0] = 1;
    for (int i(1); i <= n; ++i) cin >> a[i];
    s = accumulate(a + 1, a + n + 1, 0);
    m = *max_element(a + 1, a + n + 1);
    for (int i(0); i != m; ++i) f[i + 1] = (f[i] - inv(s - i)) % P;
    for (int i(0); i != m; ++i) f[i + 1] = (f[i + 1] + f[i]) % P;
    for (int i(0); i <= m; ++i) f[i] = 1l * (f[i] - 1) * (s - 1) % P;
    for (int i(1); i <= n; ++i) ans = (ans + f[a[i]]) % P;
    cout << (ans + P) % P << endl;
  }
}

int main() { kh::main(); }
