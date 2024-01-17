#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int mod = 998244353;
const vector<int> rs = {0, 1, 4, 6, 8, 9};

int f[2][2][3][2][2][2][3][N];
int r[N];

void add(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
int dp(int cur, int fl, int e1, int e9, int c8, int c9, int d1, int d2) {
  if (cur == -1) return 1;
  int &res = f[fl][e1][e9][c8][c9][d1][d2][cur];
  if (~res) return res;
  int mx = fl ? r[cur] : 9;
  res = 0;
  for (auto &x : rs) {
    if (x > mx) break;
    if (x == 1 && (e1 || d1 || d2 == 2)) continue;
    if (x == 9 && (e9 == 2)) continue;
    if (x == 0) {
      int nx = e9;
      if (nx == 1) nx = 2;
      add(res, dp(cur - 1, fl & (x == mx), e1, nx, c8, c9, d1, c9 * min(d2 + 1, 2)));
      continue;
    }
    if (x == 4 || x == 6) {
      int nx = e9;
      if (x == 4 && nx <= 1) nx++;
      add(res, dp(cur - 1, fl & (x == mx), 1, nx, c8, c9, d1, d2));
      continue;
    }
    if (x == 1) {
      add(res, dp(cur - 1, fl & (x == mx), 1, 2, c8, c9, d1, d2));
      continue;
    }
    if (x == 8) {
      add(res, dp(cur - 1, fl & (x == mx), e1, 2, 1, c9, d1 | c8, d2));
      continue;
    }
    if (x == 9) {
      int nx = e9;
      if (nx == 1) nx = 2;
      add(res, dp(cur - 1, fl & (x == mx), e1, nx, c8, 1, d1 | c9, d2));
      continue;
    }
  }
  return res;
}

inline int calc(const string &s) {
  int len = s.size();
  for (int i = 0; i < len; i++) {
    r[i] = s[len - i - 1] - '0';
  }
  memset(f, -1, sizeof f);
  return dp(len - 1, 1, 0, 0, 0, 0, 0, 0);
}

string del(string s) {
  int len = s.size(), cur = len - 1;
  while (s[cur] == '0') {
    s[cur] = '9';
    cur--;
  }
  s[cur]--;
  return s;
}

int main() {
  freopen("prime.in", "r", stdin);
  freopen("prime.out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    int res = mod - calc(del(s));
    cin >> s;
    (res += calc(s)) %= mod;
    cout << res << "\n";
  }
  return 0;
}