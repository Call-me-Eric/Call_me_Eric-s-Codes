# include <bits/stdc++.h>

using namespace std;

namespace kh {
  ifstream cin("maze.in");
  ofstream cout("maze.out");
  template <typename T>
    constexpr T const& clamp(T const& a, T const& b, T const& c)
    { return a < b ? b : c < a ? c : a; }
  constexpr long P(998'244'353);
  constexpr long M(200'000);
  constexpr long X(10'000'000'000);
  constexpr long R(sqrt(X));
  class fenwick1 {
    constexpr static long N = R;
    long v[N + 1];
    public:
    constexpr fenwick1() : v() {};
    constexpr fenwick1(fenwick1&&) = default;
    constexpr fenwick1(fenwick1 const&) = default;
    constexpr fenwick1& operator=(fenwick1&&) = default;
    constexpr fenwick1& operator=(fenwick1 const&) = default;
    constexpr void add(long x, long const y)
    { while (x <= N) v[x] = (v[x] + y) % P, x += x & -x; }
    constexpr long sum(long x) const
    { long r(0); while (x) r = (r + v[x]) % P, x &= x - 1; return r; }
  };
  class trie {
    constexpr static long V = M * (__lg(X) + 1) + 1;
    long v[4][V + 1], p;
    constexpr long& touch(long& x)
    { return x ? x : x = ++p; }
    public:
    trie() : v(), p(1) {}
    void add(long const x, long const y) {
      for (long i(__lg(X)), j(1); i >= 0; --i) {
        v[3][j] += (x & ((1l << (i + 1)) - 1)) % P * y % P;
        if (x >> i & 1) {
          long const d(touch(v[0][j]));
          v[2][d] = (v[2][d] + y) % P;
          v[3][d] = (v[3][d] + (1l << i) % P * y) % P;
        }
        j = touch(v[x >> i & 1][j]);
      }
    }
    long sum(long const x) const {
      long ans(0);
      for (long i(__lg(X)), j(1); i >= 0; --i) {
        ans = (ans + (x & ((1l << (i + 1)) - 1)) % P * v[2][j]) % P;
        if (x >> i & 1 && v[0][j]) ans = (ans + v[3][v[0][j]]) % P;
        if (v[x >> i & 1][j]) j = v[x >> i & 1][j]; else break;
      }
      return ans;
    }
  };
  long m, tp;
  trie tr;
  fenwick1 sm[2];
  fenwick1 vl[4];
  long ed[5][R + 1];
  long lastans;
  inline void cmat0(long a, long v) {
    sm[1].add(0 + 1, +v);
    sm[1].add(a + 1, -v);
    sm[0].add(a + 1, a * (a + 0) % P * v % P);
    vl[0].add(0 + 1, +v);
    vl[0].add(a + 1, -v);
  }
  inline void cmat1(long a, long v) {
    sm[1].add(0 + 1, +v);
    sm[1].add(a + 1, -v);
    sm[0].add(a + 1, a * (a + 1) % P * v % P);
    vl[2].add(0 + 1, +v);
    vl[2].add(a + 1, -v);
    ed[2][a + 1] = (ed[2][a + 1] + v) % P;
  }
  inline void cmat2(long a, long v) {
    sm[1].add(0 + 1, +v);
    sm[1].add(a + 1, -v);
    sm[0].add(a + 1, a * (a + 1) % P * v % P);
    vl[1].add(0 + 1, +v);
    vl[1].add(a + 1, -v);
    ed[1][a + 1] = (ed[1][a + 1] + v) % P;
  }
  inline void cmat3(long a, long v) {
    sm[1].add(0 + 1, +v);
    sm[1].add(a + 1, -v);
    sm[0].add(a + 1, a * (a + 1) % P * v % P);
    vl[3].add(0 + 1, +v);
    vl[3].add(a + 1, -v);
    ed[3][a + 1] = (ed[3][a + 1] + v) % P;
  }
  inline void cmat4(long a, long v) {
    if (a) {
      sm[1].add(0 + 1, +v);
      sm[1].add(a + 1, -v);
      sm[0].add(a + 1, a * a % P * v % P);
      sm[0].add(a + 1, a * v % P);
      sm[0].add(a + 2, a * v % P);
      vl[2].add(0 + 1, +v);
      vl[2].add(a + 1, -v);
      ed[2][a + 1] = (ed[2][a + 1] + v) % P;
      ed[4][a + 2] = (ed[4][a + 2] + v) % P;
    } else {
      sm[0].add(1, 1 * v % P);
      sm[0].add(2, 3 * v % P);
      vl[1].add(1, +v);
      vl[1].add(3, -v);
    }
  }
  inline void cmat5(long a, long v) {
    sm[1].add(0 + 1, +v);
    sm[1].add(a + 1, -v);
    sm[0].add(a + 1, a * (a + 1) % P * v % P);
    vl[0].add(0 + 1, +v);
    vl[0].add(a + 1, -v);
    ed[0][a + 1] = (ed[0][a + 1] + v) % P;
  }
  inline long qsum(long x) {
    // cerr << __func__ << ' ' << x << endl;
    long r(sqrt(x));
    while (r * r <= x) ++r;
    while (r * r >  x) --r;
    r = (r + 1) / 2;
    long ans(tr.sum(x + 1));
    // cerr << "ans" << ' ' << ans << endl;
    ans = (ans + 1 * 1 % P * sm[0].sum(r)) % P;
    // cerr << "ans" << ' ' << ans << endl;
    ans = (ans + r * r % P * sm[1].sum(r)) % P;
    // cerr << "ans" << ' ' << ans << endl;
    long d(x - (2 * r - 1) * (2 * r - 1));
    auto const chk = [&ans, d] (long l, long r, long v) {
      // if (v) cerr << "chk" << ' ' << l << ' ' << r << ' ' << v << endl;
      ans = (ans + (clamp(d, l, r) - clamp(0l, l, r)) * v) % P;
    };
    chk(0 * r + 0, 1 * r + 0, vl[0].sum(r + 1));
    chk(7 * r - 1, 8 * r + 0, vl[0].sum(r + 1));
    chk(1 * r - 1, 3 * r + 0, vl[1].sum(r + 1));
    chk(3 * r - 1, 5 * r + 0, vl[2].sum(r + 1));
    chk(5 * r - 1, 7 * r + 0, vl[3].sum(r + 1));
    chk(7 * r - 1, 8 * r - 1, ed[0][r + 1]);
    chk(1 * r - 1, 2 * r - 1, ed[1][r + 1]);
    chk(3 * r - 1, 4 * r - 1, ed[2][r + 1]);
    chk(5 * r - 1, 6 * r - 1, ed[3][r + 1]);
    chk(3 * r - 1, 4 * r - 2, ed[4][r + 1]);
    // cerr << "ans" << ' ' << ans << endl;
    return ans;
  }
  inline void cadd(long l, long r, long v) {
    l ^= tp ? lastans : 0;
    r ^= tp ? lastans : 0;
    v ^= tp ? lastans : 0;
    tr.add(r + 1, v), tr.add(l, -v);
  }
  inline void cmat(long x, long v) {
    x ^= tp ? lastans : 0;
    v ^= tp ? lastans : 0;
    for (long const d : { -3, -2, -1, 0, +1, +2, +3 }) {
      long a(sqrt(x) + d), b;
      if (a <= 0 || x % a || abs(a - x / a) > 2) continue;
      b = x / (a = min(a, x / a));
      switch (2 * (b - a) + (a - 1) % 2) {
        case 0: cmat0((a + 1) / 2, v); break;
        case 1: cmat1((a + 1) / 2, v); break;
        case 2: cmat2((a + 1) / 2, v); break;
        case 3: cmat3((a + 1) / 2, v); break;
        case 4: cmat4((a + 0) / 2, v); break;
        case 5: cmat5((a + 0) / 2, v); break;
      }
      return;
    }
  }
  inline long qsum(long l, long r) {
    l ^= tp ? lastans : 0, r ^= tp ? lastans : 0;
    return lastans = ((qsum(r) - qsum(l - 1)) % P + P) % P;
  }
  void main() {
    cin >> m >> tp;
    for (int i(1); i <= m; ++i) {
      long o, l, r, x, v;
      switch (cin >> o, o) {
        case 1: cin >> l >> r >> v, cadd(l, r, v); break;
        case 2: cin >> x >> v, cmat(x, v); break;
        case 3: cin >> l >> r, cout << qsum(l, r) << endl; break;
      }
      // qsum(16);
    }
  }
}

int main() { kh::main(); }
