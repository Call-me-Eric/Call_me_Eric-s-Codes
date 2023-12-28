#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void setmin(int &x, int y) { if (y < x) x = y; }
inline void setmax(int &x, int y) { if (y > x) x = y; }

const int N = 100000;
const int inf = (int)1e9 + 1;

int a[N];
int min_pref[N * 3];
bool dp[N];
int gp[N];
int res[N];

void solve(int n, int W) {
  sort(a, a + n, [](int x, int y) { return x > y; });
  if (a[0] >= W) {
    for (int i = 0; i < n; i++) {
      res[i] = n;
    }
    return;
  }
  W -= a[0];
  for (int i = 0; i < N * 3; i++) {
    min_pref[i] = 0;
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (i > 0 ? a[i] : 0);
    if (sum + 1 >= N * 3) {
      break;
    }
    min_pref[sum + 1] = i + 1;
  }
  for (int i = 1; i < N * 3; i++) {
    min_pref[i] = max(min_pref[i - 1], min_pref[i]);
  }
  int ans = n;
  for (int i = 0; i < W; i++) {
    dp[i] = false;
  }
  dp[0] = true;
  int p = 1;
  while (p < n) {
    if (p >= ans) {
      break;
    }
    int p1 = p + 1;
    while (p1 < n && a[p1] == a[p]) {
      p1++;
    }
    for (int j = max(0LL, W - (ll)a[p] * (p1 - p)); j < W; j++) {
      if (!dp[j]) {
        continue;
      }
      int cnt = (W - j + (a[p] - 1)) / a[p];
      if (cnt > (p1 - p)) {
        continue;
      }
      int need_sum = (j + a[p] * cnt) + W;
      int pos = min_pref[need_sum];
      pos = max(pos, p + cnt);
      setmin(ans, pos);
    }
    for (int j = 0; j < W; j++) {
      if (dp[j]) {
        gp[j] = 0;
      }
      else {
        gp[j] = inf;
        if (j >= a[p]) {
          setmin(gp[j], gp[j - a[p]] + 1);
        }
      }
      if (!dp[j]) {
        dp[j] = (gp[j] <= (p1 - p));
        if (j < a[p]) {
          assert(gp[j] == inf);
        }
        else if (j > a[p]) {
          if (j > ((long long)a[p] * gp[j])) {
            if (gp[j] <= (p1 - p)) {
              assert(dp[j - a[p] * gp[j]]);
            }
          }
        }
      }
    }
    p = p1;
  }
  int pos = min_pref[W];
  for (int i = 0; i < n; i++) {
    res[i] = max((ans < n ? (n - 1) - (ans - 2) : 0), max(i, n - i - 1) - (pos - 1));
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.precision(20);
  cout << fixed;
  int T;
  cin >> T;
  while (T--) {
    int n, W;
    cin >> n >> W;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve(n, W);
    for (int i = 0; i < n; i++) {
      cout << res[i] << (i < n - 1 ? " " : "\n");
    }
  }
  return 0;
}
