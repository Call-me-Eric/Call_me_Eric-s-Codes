# include <bits/stdc++.h>
# include <bits/extc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("unpredictable.in");
  ofstream cout("unpredictable.out");
  using pair = std::pair<int, int>;
  constexpr size_t N(1'000'100);
  constexpr int P(998'244'353);
  constexpr int Q[]{ 881'965'171, 873'469'837 };
  int pow[2][N];
  struct hash_func {
    constexpr static uint64_t Q[]{ 282'909'488'123, 170'657'935'489 };
    constexpr uint64_t operator()(pair const &v) const
    { return v.first * Q[0] + v.second * Q[1]; }
  };
  __gnu_pbds::gp_hash_table<pair, int, hash_func> f[N], g[N];
  struct skill {
    int n;
    vector<char> s;
    vector<int> w, nxt, nxtr;
    vector<int> h[2], rh[2];
    inline void init() {
      string j; cin >> j;
      n = j.size();
      s.resize(n + 1), w.resize(n + 1);
      nxt.resize(n + 1), nxtr.resize(n + 1);
      h[0].resize(n + 2), h[1].resize(n + 2);
      rh[0].resize(n + 2), rh[1].resize(n + 2);
      for (int i(1); i <= n; ++i) s[i] = j[i - 1];
      for (int i(1); i <= n; ++i) cin >> w[i];
      for (int i(2), j(0); i <= n; ++i) {
        while (j && s[j + 1] != s[i]) j = nxt[j];
        if (s[j + 1] == s[i]) ++j;
        nxt[i] = j;
      }
      reverse(s.begin() + 1, s.begin() + n + 1);
      for (int i(2), j(0); i <= n; ++i) {
        while (j && s[j + 1] != s[i]) j = nxtr[j];
        if (s[j + 1] == s[i]) ++j;
        nxtr[i] = j;
      }
      reverse(s.begin() + 1, s.begin() + n + 1);
      for (int i(1); i <= n; ++i) {
        h[0][i] = (h[0][i - 1] * 712l + s[i]) % Q[0];
        h[1][i] = (h[1][i - 1] * 831l + s[i]) % Q[1];
      }
      for (int i(n); i >= 1; --i) {
        rh[0][i] = (rh[0][i + 1] + 1l * s[i] * pow[0][n - i]) % Q[0];
        rh[1][i] = (rh[1][i + 1] + 1l * s[i] * pow[1][n - i]) % Q[1];
      }
    }
    inline void ins() const {
      for (int i(1); i <= n; ++i) {
        auto const j(pair(rh[0][n - i + 1], rh[1][n - i + 1]));
        auto const r((w[i] - w[nxtr[i]] + P) % P);
        f[i][j] = (f[i][j] + 1) % P;
        g[i][j] = (g[i][j] + r) % P;
      }
    }
    inline void era() const {
      for (int i(1); i <= n; ++i) {
        auto const j(pair(rh[0][n - i + 1], rh[1][n - i + 1]));
        auto const r((w[i] - w[nxtr[i]] + P) % P);
        f[i][j] = (f[i][j] + P - 1) % P;
        g[i][j] = (g[i][j] + P - r) % P;
      }
    }
    inline int calc() const {
      auto res(0);
      era();
      for (int i(1); i <= n; ++i) {
        auto const j(pair(h[0][i], h[1][i]));
        auto const v((w[i] - w[nxt[i]] + P) % P);
        res = (res + 1l * f[i][j] * v % P) % P;
        res = (res + g[i][j]) % P;
      }
      ins();
      return res;
    }
  } v[N];
  int n, ans;
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    pow[0][0] = pow[1][0] = 1;
    for (int i(1); i <= 1'000'000; ++i) {
      pow[0][i] = pow[0][i - 1] * 712l % Q[0];
      pow[1][i] = pow[1][i - 1] * 831l % Q[1];
    }
    for (int i(1); i <= n; ++i) v[i].init(), v[i].ins();
    for (int i(1); i <= n; ++i) ans = (ans + v[i].calc()) % P;
    for (int i(1); i <= n - 2; ++i) ans = 1l * ans * i % P;
    ans = 1l * (n - 1) * ans % P;
    cout << ans << endl;
  }
}

int main() { lyre::main(); }
