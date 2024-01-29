# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("lct.in");
  ofstream cout("lct.out");
  constexpr size_t N(200'100);
  int n, q, cnt;
  int ans[N];
  struct query {
    int type, x, l, r, sgn;
    constexpr query() : type(), x(), l(), r(), sgn() {}
    constexpr query(int t, int x, int l, int r, int s)
      : type(t), x(x), l(l), r(r), sgn(s) {}
    constexpr bool operator<(query const &b) const {
      if (x != b.x) return x < b.x;
      return type < b.type;
    }
  } qry[N * 4];
  class fenwick_tree {
    int n, tr[N];
    public:
    inline void init(int _n)
    { n = _n, memset(tr + 1, 0x00, sizeof(int[n])); }
    inline void add(int x, int v)
    { ++x; while (x <= n) tr[x] += v, x += x & -x; }
    inline int query(int x) const
    { ++x; int r(0); while (x) r += tr[x], x &= x - 1; return r; }
    inline int qsum(int l, int r) const
    { return query(r) - query(l - 1); }
  } bit;
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    bit.init(n + 1);
    for (int i(1); i < n; ++i) {
      int x, y;
      cin >> x >> y;
      if (x > y) swap(x, y);
      qry[cnt++] = query(-1, x, y, y, +1);
    }
    for (int i(0); i < q; ++i) {
      int x, y;
      cin >> x >> y;
      qry[cnt++] = query(i, x - 1, x, y, -1);
      qry[cnt++] = query(i, y, x, y, +1);
      ans[i] = y - x + 1;
    }
    sort(qry, qry + cnt);
    for (int i(0); i < cnt; ++i) {
      auto [type, x, l, r, s](qry[i]);
      if (~type) {
        ans[type] -= s * bit.qsum(l, r);
      } else {
        bit.add(l, +1);
      }
    }
    for (int i(0); i < q; ++i)
      cout << ans[i] << '\n';
  }
}

int main() { lyre::main(); }