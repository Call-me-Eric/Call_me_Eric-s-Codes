# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("ur.in");
  ofstream cout("ur.out");
  int n, k, ans;
  inline int calc(int d)
  { return k / (n / d) * (n / d); }
  inline void print(int d) {
    for (int i(0); i < n; ++i)
      cout << (i % d < k / (n / d));
    cout << endl;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i(2); i * i <= n; ++i) {
      if (n % i) continue;
      ans = max(ans, calc(i));
      ans = max(ans, calc(n / i));
    }
    for (int i(2); i * i <= n; ++i) {
      if (n % i) continue;
      if (calc(i) == ans) return print(i);
      if (calc(n / i) == ans) return print(n / i);
    }
    for (int i(0); i < n; ++i) cout << 0;
    cout << endl;
  }
}

int main() { lyre::main(); }