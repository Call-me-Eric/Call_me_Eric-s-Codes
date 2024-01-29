#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int M = 1e6 + 5;
const int mod = 998244353;

inline int qp(int a, int b = mod - 2) {
  int res = 1;
  for (; b; a = 1ll * a * a % mod, b >>= 1)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
int fac[M], ifac[M];
void Init(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[n] = qp(fac[n]);
  for (int i = n; i; i--) ifac[i - 1] = 1ll * ifac[i] * i % mod;
}
int binom(int n, int m) {
  if (n < m || m < 0) return 0;
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, m, k, a[N], b[N];
int f[N], ans;

void dfs(int st) {
  if (st == k) {
    int fl = 1;
    for (int i = 1; i <= n; ++i) fl &= (a[i] == b[i]);
    (ans += fl);
    return;
  }
  int d = 0;
  for (int i = 1; i <= n; ++i) {
    d += abs(a[i] - b[i]);
  }
  if (d > k - st) return;
  for (int i = 1; i <= n; ++i) {
    a[i]++;
    if (i > 1 && a[i] > a[i - 1]) {

    } else {
      dfs(st + 1);
    }
    a[i]--;
  }
  for (int i = 1; i <= n; ++i) {
    a[i]--;
    if (a[i] < 0 || a[i] < a[i + 1]) {

    } else {
      dfs(st + 1);
    }
    a[i]++;
  }
}

int main() {
  freopen("young.in", "r", stdin);
  freopen("young.out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
  }
  n = max(n, m) + 1;
  int q;
  cin >> q;
  cin >> k;
  dfs(0);
  cout << ans << "\n";
  return 0;
}