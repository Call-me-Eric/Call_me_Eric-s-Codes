# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("dark.in");
  ofstream cout("dark.out");
  constexpr size_t N(50'100);
  constexpr int P(134'775'813);
  constexpr int Q[]{ 1'103'515'245, 1'013'904'223 };
  int n, m;
  pair<long, long> v[N];
  inline int& add(int &a, int const b)
  { return (a += b) >= m ? a -= m : a; }
  struct matrix {
    int v[2][2];
    constexpr matrix() : v() {}
    constexpr int& operator()(int i, int j) { return v[i][j]; }
    constexpr int operator()(int i, int j) const { return v[i][j]; }
    inline matrix operator*(matrix const &b) const {
      matrix r;
      for (int i(0); i < 2; ++i) {
        for (int j(0); j < 2; ++j) {
          add(r(i, j), 1l * v[i][0] * b(0, j) % m);
          add(r(i, j), 1l * v[i][1] * b(1, j) % m);
        }
      }
      return r;
    }
  };
  namespace sub3 {
    class fenwick_tree {
      constexpr static int N = 10'000;
      int v[2 * N + 100];
      public:
      constexpr fenwick_tree() : v() {}
      inline void add(int x, int const y)
      { x += N; while (x <= 2 * N) v[x] += y, x += x & -x; }
      inline uint32_t qsum(int x) const
      { x += N; auto r(0u); while (x) r += v[x], x &= x - 1; return r; }
    };
    inline int calc(long n) {
      matrix s, t;
      n -= 1;
      s(0, 0) = P % m;
      t(0, 0) = Q[0] % m;
      t(1, 0) = Q[1] % m;
      s(0, 1) = t(1, 1) = 1;
      while (n) {
        if (n & 1) s = s * t;
        n >>= 1, t = t * t;
      }
      return s(0, 0);
    }
    inline uint32_t solve(long l, long r) {
      static int u[N], cnt1[N], cnt4[N];
      u[0] = calc(l);
      cnt1[0] = !(u[0] % 4);
      cnt4[0] = (u[0] & 1);
      for (int i(1); i <= r - l; ++i) {
        u[i] = (1l * u[i - 1] * Q[0] + Q[1]) % m;
        cnt1[i] = cnt1[i - 1] + !(u[i] % 4);
        cnt4[i] = cnt4[i - 1] + (u[i] & 1);
      }
      auto res(0u);
      static fenwick_tree tr;
      tr.add(0, +1);
      for (int i(0); i <= r - l; ++i) {
        res += tr.qsum(cnt4[i] - 2 * cnt1[i] - 1);
        tr.add(cnt4[i] - 2 * cnt1[i], +1);
      }
      tr.add(0, -1);
      for (int i(0); i <= r - l; ++i)
        tr.add(cnt4[i] - 2 * cnt1[i], -1);
      return res;
    }
    bool main() {
      if (n > 2'000) return false;
      for (int i(1); i <= n; ++i) {
        auto const &[l, r](v[i]);
        if (r - l + 1 > 2'000)
          return false;
      }
      for (int i(1); i <= n; ++i) {
        auto const &[l, r](v[i]);
        cout << solve(l, r) << '\n';
      }
      return true;
    }
  }
  namespace sub4 {
    constexpr int R(300'100);
    constexpr int B(2000);
    int s[R], w[R];
    uint32_t ans[N];
    class fenwick_tree {
      constexpr static int N = 600'000;
      int v[2 * N + 100];
      public:
      constexpr fenwick_tree() : v() {}
      inline void add(int x, int const y)
      { x += N; while (x <= 2 * N) v[x] += y, x += x & -x; }
      inline uint32_t qsum(int x) const
      { x += N; auto r(0u); while (x) r += v[x], x &= x - 1; return r; }
    } bit;
    struct query {
      int l, r, index;
      constexpr query() : l(), r(), index() {}
      constexpr query(int l, int r, int index)
        : l(l), r(r), index(index) {}
      constexpr bool operator<(query const &b) const {
        if (l / B != b.l / B) return l < b.l;
        return r < b.r;
      }
    } u[N];
    uint32_t cur;
    inline void eraL(int const x) {
      cur -= bit.qsum(R) - bit.qsum(w[x]);
      bit.add(w[x], -1);
    }
    inline void eraR(int const x) {
      cur -= bit.qsum(w[x] - 1);
      bit.add(w[x], -1);
    }
    inline void insL(int const x) {
      cur += bit.qsum(R) - bit.qsum(w[x]);
      bit.add(w[x], +1);
    }
    inline void insR(int const x) {
      cur += bit.qsum(w[x] - 1);
      bit.add(w[x], +1);
    }
    bool main() {
      for (int i(1); i <= n; ++i) {
        auto const &[l, r](v[i]);
        if (r > 300'000) return false;
      }
      s[1] = P;
      for (int i(2); i <= 300'000; ++i)
        s[i] = (1l * s[i - 1] * Q[0] + Q[1]) % m;
      for (int i(1); i <= 300'000; ++i) {
        w[i] = w[i - 1];
        if (s[i] & 1) w[i] += 1;
        else if (!(s[i] % 4)) w[i] -= 2;
      }
      for (int i(1); i <= n; ++i) {
        auto const &[l, r](v[i]);
        u[i] = query(l - 1, r, i);
      }
      auto pl(0), pr(0);
      bit.add(0, +1);
      sort(u + 1, u + n + 1);
      for (int i(1); i <= n; ++i) {
        auto const &[l, r, x](u[i]);
        while (pr < r) insR(++pr);
        while (pl > l) insL(--pl);
        while (pr > r) eraR(pr--);
        while (pl < l) eraL(pl++);
        ans[x] = cur;
      }
      for (int i(1); i <= n; ++i)
        cout << ans[i] << '\n';
      return true;
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i(1); i <= n; ++i) {
      auto &[l, r](v[i]);
      cin >> l >> r;
    }
    if (sub3::main()) return;
    if (sub4::main()) return;
    assert(false);
  }
}

int main() { lyre::main(); }
