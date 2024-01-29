#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<int MOD>
struct ModInt {
  int x;
 
  ModInt() : x(0) {}
  ModInt(i64 y) : x(y >= 0 ? y % MOD : (MOD - (-y) % MOD) % MOD) {}

  inline int inc(const int &x) {
    return x >= MOD ? x - MOD : x;
  }
  inline int dec(const int &x) {
    return x < 0 ? x + MOD : x;
  }
 
  ModInt &operator+= (const ModInt &p) {
    x = inc(x + p.x);
    return *this;
  } 
  ModInt &operator-= (const ModInt &p) {
    x = dec(x - p.x);
    return *this;
  }
 
  ModInt &operator*= (const ModInt &p) {
    x = (int)(1ll * x * p.x % MOD);
    return *this;
  }
  ModInt &operator/= (const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
 
  ModInt operator-() const { return ModInt(-x); } 

  friend ModInt operator + (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) += rhs;
  }
  friend ModInt operator - (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) -= rhs;
  }
  friend ModInt operator * (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) *= rhs;
  }
  friend ModInt operator / (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) /= rhs;
  }
 
  bool operator == (const ModInt &p) const { return x == p.x; } 
  bool operator != (const ModInt &p) const { return x != p.x; }
 
  ModInt inverse() const {
    int a = x, b = MOD, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }

  ModInt pow(i64 n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
 
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
 
  friend istream &operator>>(istream &is, ModInt &a) {
    i64 t;
    is >> t;
    a = ModInt<MOD>(t);
    return (is);
  }
  static int get_mod() { return MOD; }
};

const int MOD = 998244353;

using MInt = ModInt<MOD>;
MInt pow(i64 n, i64 x) { return MInt(n).pow(x); }
MInt pow(MInt n, i64 x) { return n.pow(x); }

const int N = 5000 + 5;

int n , m , la[N] , lb[N];
int a[N] , b[N];

int La[N] , Ra[N];
int Lb[N] , Rb[N];

MInt f[N][N] , sf[N][N];
MInt suba[N] , subb[N];

MInt g[N][N] , sg[N][N];
MInt h[N][N] , sh[N][N];

int main() {
  freopen("subsequence.in", "r", stdin);
  freopen("subsequence.out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(0);

  cin >> n >> m;
  for (int i = 1 ; i <= n ; i++) {
    cin >> a[i];
    La[i] = la[a[i]];
    la[a[i]] = i;
  }
  for (int i = 1 ; i <= m ; i++) {
    cin >> b[i];
    Lb[i] = lb[b[i]];
    lb[b[i]] = i;
  }
  for (int i = 1 ; i <= 100 ; i++) {
    la[i] = n + 1;
    lb[i] = m + 1;
  }
  for (int i = n ; i >= 1 ; i--) {
    Ra[i] = la[a[i]];
    la[a[i]] = i;
  }
  for (int i = m ; i >= 1 ; i--) {
    Rb[i] = lb[b[i]];
    lb[b[i]] = i;
  }

  f[0][0] = sf[0][0] = 1;
  for (int i = 1 ; i <= n ; i++) {
    sf[0][i] = sf[0][i - 1] + f[0][i];
  }
  auto qrysf = [&](int i , int l , int r) {
    auto ret = sf[i][r];
    if (l > 0) ret -= sf[i][l - 1];
    return ret;
  };

  for (int i = 1 ; i <= n ; i++) {
    for (int j = 1 ; j <= n ; j++) {
      f[i][j] = qrysf(i - 1 , La[j] , j - 1);
      sf[i][j] = sf[i][j - 1] + f[i][j];
    }
  }
  for (int i = 1 ; i <= n ; i++) {
    suba[i] = sf[i][n];
  }
  f[0][0] = sf[0][0] = 1;
  for (int i = 1 ; i <= m ; i++) {
    sf[0][i] = sf[0][i - 1] + f[0][i];
  }
  for (int i = 1 ; i <= m ; i++) {
    for (int j = 1 ; j <= m ; j++) {
      // cout << j << ":" << Lb[j] << endl;
      // cout << qrysf(i - 1 , Lb[j] , j - 1) << endl;
      f[i][j] = qrysf(i - 1 , Lb[j] , j - 1);
      sf[i][j] = sf[i][j - 1] + f[i][j];
    }
  }
  for (int i = 1 ; i <= m ; i++) {
    subb[i] = sf[i][m];
  }
  // for (int i = 1 ; i <= n ; i++) {
  //   cout << suba[i] << ' ';
  // }
  // cout << endl;
  // for (int i = 1 ; i <= m ; i++) {
  //   cout << subb[i] << ' ';
  // }
  // cout << endl;

  MInt ans = 0 , s = 0;
  for (int i = 1 ; i <= n ; i++) {
    ans += s * suba[i];
    s += subb[i];
  }
  // cout << ans << endl;

  auto qry1 = [&](int x1 , int x2 , int y1 , int y2) {
    // cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << ":";
    auto ret = sg[x2][y2];
    if (x1 >= 1) ret -= sg[x1 - 1][y2];
    if (y1 >= 1) ret -= sg[x2][y1 - 1];
    if (x1 >= 1 && y1 >= 1) ret += sg[x1 - 1][y1 - 1];
    // cout << ret << endl;
    return ret;
  };

  g[0][0] = sg[0][0] = 1;
  for (int i = 1 ; i <= m ; i++) {
    sg[0][i] = sg[0][i - 1] + g[0][i];
  }
  for (int i = 1 ; i <= n ; i++) {
    sg[i][0] = sg[i - 1][0];
    for (int j = 1 ; j <= m ; j++) {
      if (a[i] == b[j]) g[i][j] = qry1(La[i] , i - 1 , Lb[j] , j - 1);
      sg[i][j] = sg[i - 1][j] + sg[i][j - 1] - sg[i - 1][j - 1] + g[i][j];
    }
  }

  auto qry2 = [&](int x1 , int x2 , int y1 , int y2) {
    // cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << endl;
    // cout << sh[x1][y1] - sh[x2 + 1][y1] - sh[x1][y2 + 1] + sh[x2 + 1][y2 + 1] << endl;
    return sh[x1][y1] - sh[x2 + 1][y1] - sh[x1][y2 + 1] + sh[x2 + 1][y2 + 1];
  };

  h[n + 1][m + 1] = sh[n + 1][m + 1] = 1;
  for (int i = m ; i >= 1 ; i--) {
    sh[n + 1][i] = sh[n + 1][i + 1] + h[n + 1][i];
  }
  for (int i = n ; i >= 1 ; i--) {
    sh[i][m + 1] = sh[i + 1][m + 1];
    for (int j = m ; j >= 1 ; j--) {
      h[i][j] = qry2(i + 1 , Ra[i] , j + 1 , Rb[j]);
      sh[i][j] = sh[i + 1][j] + sh[i][j + 1] - sh[i + 1][j + 1] + h[i][j];
    }
  }

  // for (int i = 1 ; i <= n ; i++) {
  //   for (int j = 1 ; j <= m ; j++) {
  //     cout << g[i][j] << ' ';
  //   }
  //   cout << endl;
  // }

  // for (int i = 1 ; i <= n ; i++) {
  //   for (int j = 1 ; j <= m ; j++) {
  //     cout << h[i][j] << ' ';
  //   }
  //   cout << endl;
  // }

  for (int i = 1 ; i <= n ; i++) {
    for (int j = 1 ; j <= m ; j++) {
      if (a[i] > b[j]) {
        ans += qry1(La[i] , i - 1 , Lb[j] , j - 1) * sh[i + 1][j + 1];
      }
    }
  }

  cout << ans << endl;
  return 0;
}