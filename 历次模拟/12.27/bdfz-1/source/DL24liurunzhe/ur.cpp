# include <cstdio>
# include <vector>
# include <cmath>
# include <algorithm>
# include <functional>

int main() {

  freopen("ur.in", "r", stdin);
  freopen("ur.out", "w", stdout);

  int n, k;
  scanf("%d %d", &n, &k);

  if (k == n) {
    for (int i = 1; i <= n; ++i)
      putchar('1'); putchar('\n'); return 0;
  }

  if (k <= 1) {
    for (int i = 1; i <= n; ++i) 
      putchar('0'); putchar('\n'); return 0;
  }

  std::vector<int> vec;

  int x = n;
  for (int i = 2; i <= x; ++i) {
    if (x % i == 0) vec.push_back(i);
    while (x % i == 0) x /= i;
  }
  if (x > 1) vec.push_back(x);

  if (vec.size() == 1) {
    std::vector<int> ans(n + 1);

    int cnt = k / vec[0];
    for (int i = 1; i <= vec[0]; ++i) {
      int st = 1 + (i - 1) * (n / vec[0]);
      for (int j = st; j <= st + cnt - 1; ++j) {
        ans[j] = 1;
      }
    }

    for (int i = 1; i <= n; ++i)
      putchar(ans[i] + '0'); putchar('\n'); return 0;
  }

  if (vec.size() == 2) {
    int mx = 0, a = 0, b = 0;
    for (int i = 0; i <= n; ++i) {
      if (vec[0] * i > k) break;
      int cnt = n / vec[1] - vec[0] * ceil(i * 1.0 / vec[1]);
      int rem = k - vec[0] * i;
      int tot = std::min(rem / vec[1], cnt) * vec[1] + vec[0] * i;
      if (tot > mx) {
        mx = tot, a = i;
        b = std::min(rem / vec[1], cnt);
      }
    }

    std::vector<int> ans(n + 1);

    int circ = a / vec[1], rem = a % vec[1];

    for (int i = 1; i <= circ; ++i) {
      for (int st = i, flg = 0; st != i || !flg; flg = true, st = (st + n / vec[1] - 1) % n + 1) {
        for (int j = st, flgg = 0; j != st || !flgg; flgg = true, j = (j + n / vec[0] - 1) % n + 1) {
          ans[j] = 1;
        }
      }
    }

    for (int st = circ + 1; rem --; st = (st + n / vec[1] - 1) % n + 1) {
      for (int j = st, flg = 0; j != st || !flg; flg = true, j = (j + n / vec[0] - 1) % n + 1) {
        ans[j] = 1;
      }
    }

    int s = 0;
    for (int i = 1; i <= n / vec[1]; ++i) {
      bool flg = true;
      for (int j = i; j <= n; j += n / vec[1])
        if (ans[j]) { flg = false; break; }
      
      if (flg) {
        ++s;
        for (int j = i; j <= n; j += n / vec[1])
          ans[j] = 1;
      }
      if (s == b) break;
    }

    for (int i = 1; i <= n; ++i)
      putchar(ans[i] + '0'); putchar('\n'); return 0;
  }

  if (n == 30) {
    bool flg1, flg2, flg3;
    int mx = 0, a = 0, b = 0;

    vec[0] = 2, vec[1] = 3;
    for (int i = 0; i <= n; ++i) {
      if (vec[0] * i > k) break;
      int cnt = n / vec[1] - vec[0] * ceil(i * 1.0 / vec[1]);
      int rem = k - vec[0] * i;
      int tot = std::min(rem / vec[1], cnt) * vec[1] + vec[0] * i;
      if (tot > mx) {
        flg1 = true, flg2 = flg3 = false;
        mx = tot, a = i;
        b = std::min(rem / vec[1], cnt);
      }
    }

    vec[0] = 2, vec[1] = 5;
    for (int i = 0; i <= n; ++i) {
      if (vec[0] * i > k) break;
      int cnt = n / vec[1] - vec[0] * ceil(i * 1.0 / vec[1]);
      int rem = k - vec[0] * i;
      int tot = std::min(rem / vec[1], cnt) * vec[1] + vec[0] * i;
      if (tot > mx) {
        flg2 = true, flg1 = flg3 = false;
        mx = tot, a = i;
        b = std::min(rem / vec[1], cnt);
      }
    }

    vec[0] = 3, vec[1] = 5;
    for (int i = 0; i <= n; ++i) {
      if (vec[0] * i > k) break;
      int cnt = n / vec[1] - vec[0] * ceil(i * 1.0 / vec[1]);
      int rem = k - vec[0] * i;
      int tot = std::min(rem / vec[1], cnt) * vec[1] + vec[0] * i;
      if (tot > mx) {
        flg3 = true, flg1 = flg2 = false;
        mx = tot, a = i;
        b = std::min(rem / vec[1], cnt);
      }
    }

    if (flg1) vec[0] = 2, vec[1] = 3;
    if (flg2) vec[0] = 2, vec[1] = 5;
    if (flg3) vec[0] = 3, vec[1] = 5;

    std::vector<int> ans(n + 1);

    int circ = a / vec[1], rem = a % vec[1];

    for (int i = 1; i <= circ; ++i) {
      for (int st = i, flg = 0; st != i || !flg; flg = true, st = (st + n / vec[1] - 1) % n + 1) {
        for (int j = st, flgg = 0; j != st || !flgg; flgg = true, j = (j + n / vec[0] - 1) % n + 1) {
          ans[j] = 1;
        }
      }
    }

    for (int st = circ + 1; rem --; st = (st + n / vec[1] - 1) % n + 1) {
      for (int j = st, flg = 0; j != st || !flg; flg = true, j = (j + n / vec[0] - 1) % n + 1) {
        ans[j] = 1;
      }
    }

    int s = 0;
    for (int i = 1; i <= n / vec[1]; ++i) {
      bool flg = true;
      for (int j = i; j <= n; j += n / vec[1])
        if (ans[j]) { flg = false; break; }
      
      if (flg) {
        ++s;
        for (int j = i; j <= n; j += n / vec[1])
          ans[j] = 1;
      }
      if (s == b) break;
    }

    for (int i = 1; i <= n; ++i)
      putchar(ans[i] + '0'); putchar('\n'); return 0;
  }

  return 0;
}