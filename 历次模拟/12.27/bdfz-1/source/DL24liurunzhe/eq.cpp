# include <cstdio>
# include <vector>
# include <algorithm>
# include <functional>

# define int long long

constexpr int MOD = 998244353;

signed main() {

  freopen("eq.in", "r", stdin);
  freopen("eq.out", "w", stdout);

  auto fpow = [&](int x, int k) {
    int res = 1;
    for (; k; k >>= 1) {
      if (k & 1) res = res * x % MOD;
      x = x * x % MOD;
    }
    return res;
  };

  auto inv = [&](int x) {
    return fpow(x, MOD - 2);
  };

  int n, q, a, b;

  scanf("%lld %lld %lld %lld", &n, &q, &a, &b);

  if (a == 0 && b == 0) puts("Many");
  else if (a == 0 && b != 0) puts("No");
  else printf("%lld\n", b * inv(a) % MOD);

  for (int i = 1; i <= q; ++i) {
    scanf("%*d %lld %lld", &a, &b);
    if (a == 0 && b == 0) puts("Many");
    else if (a == 0 && b != 0) puts("No");
    else printf("%lld\n", b * inv(a) % MOD);
  }

  return 0;
}