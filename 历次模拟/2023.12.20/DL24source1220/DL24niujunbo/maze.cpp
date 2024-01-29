# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("maze.in");
  ofstream cout("maze.out");
  constexpr size_t M(200'100);
  constexpr long V(10'000'000'000);
  constexpr int P(998'244'353);
  int m, type;
  tuple<int, long, long, int> v[M];
  namespace sub5 {
    namespace seg {
      constexpr size_t N(M * 60);
      struct node {
        int ls, rs, sum, tag;
        constexpr node() : ls(), rs(), sum(), tag() {}
        inline void apply(int v, long l, long r) {
          sum = (sum + 1l * (r - l + 1) * v) % P;
          tag = (tag + v) % P;
        }
      } tr[N];
      int tot = 0;
      inline void up(int x) {
        assert(x);
        auto const ls(tr[x].ls), rs(tr[x].rs);
        tr[x].sum = (tr[ls].sum + tr[rs].sum) % P;
      }
      inline void down(int x, long l, long r) {
        assert(x);
        if (!tr[x].tag) return;
        auto &ls(tr[x].ls), &rs(tr[x].rs);
        auto const mid((l + r) / 2);
        if (!ls) ls = ++tot;
        if (!rs) rs = ++tot;
        tr[ls].apply(tr[x].tag, l, mid);
        tr[rs].apply(tr[x].tag, mid + 1, r);
        tr[x].tag = 0;
      }
      void add(int &u, long l, long r, long x, long y, int z) {
        if (!u) u = ++tot;
        if (l == x && r == y) return tr[u].apply(z, l, r);
        down(u, l, r);
        auto const mid((l + r) / 2);
        if (y <= mid) {
          add(tr[u].ls, l, mid, x, y, z);
        } else if (x > mid) {
          add(tr[u].rs, mid + 1, r, x, y, z);
        } else {
          add(tr[u].ls, l, mid, x, mid, z);
          add(tr[u].rs, mid + 1, r, mid + 1, y, z);
        }
        up(u);
      }
      int qsum(int u, long l, long r, long x, long y) {
        if (!u) return 0;
        if (l == x && r == y) return tr[u].sum;
        down(u, l, r);
        auto const mid((l + r) / 2);
        if (y <= mid)
          return qsum(tr[u].ls, l, mid, x, y);
        if (x > mid)
          return qsum(tr[u].rs, mid + 1, r, x, y);
        return (qsum(tr[u].ls, l, mid, x, mid)
              + qsum(tr[u].rs, mid + 1, r, mid + 1, y)) % P;
      }
    }
    bool main() {
      for (int i(1); i <= m; ++i) {
        if (get<0>(v[i]) == 2)
          return false;
      }
      auto lastans(0), root(0);
      for (int i(1); i <= m; ++i) {
        auto [opt, x, y, z](v[i]);
        x ^= type * lastans;
        y ^= type * lastans;
        z ^= type * lastans;
        if (opt == 1) {
          seg::add(root, 1, V, x, y, z);
        } else {
          lastans = seg::qsum(root, 1, V, x, y);
          cout << lastans << '\n';
        }
      }
      return true;
    }
  }
  namespace sub1 {
    constexpr int N(3'000);
    constexpr int dx[]{ 0, -1, 0, +1 };
    constexpr int dy[]{ +1, 0, -1, 0 };
    using vertex = pair<int, int>;
    map<vertex, int> index;
    vertex pos[N];
    int val[N];
    bool main() {
      pos[1] = vertex(0, 0);
      index[vertex(0, 0)] = 1;
      auto x(0), y(1), cur(3), k(1);
      for (int i(2); i <= 2'500; ++i) {
        pos[i] = vertex(x, y);
        index[vertex(x, y)] = i;
        if (i == (cur - 2) * (cur - 2) + 1) k = 1;
        auto const d(i - (cur - 2) * (cur - 2));
        if (i != cur * cur && !(d % (cur - 1))) k = (k + 1) % 4;
        if (i == cur * cur) cur += 2;
        x += dx[k], y += dy[k];
      }
      auto lastans(0);
      for (int i(1); i <= m; ++i) {
        auto [opt, x, y, z](v[i]);
        x ^= type * lastans;
        y ^= type * lastans;
        z ^= type * lastans;
        if (opt == 1) {
          for (int i(x); i <= y; ++i)
            val[i] = (val[i] + z) % P;
        } else if (opt == 2) {
          auto const &[a, b](pos[x]);
          for (int i(1); i <= 2500; ++i) {
            auto const [u, v](pos[i]);
            if (min(0, a) <= u && u <= max(0, a)) {
              if (min(0, b) <= v && v <= max(0, b))
                val[i] = (val[i] + y) % P;
            }
          }
        } else {
          auto res(0);
          for (int i(x); i <= y; ++i)
            res = (res + val[i]) % P;
          cout << res << '\n';
        }
      }
      return true;
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> type;
    for (int i(1); i <= m; ++i) {
      auto &[opt, x, y, z](v[i]);
      cin >> opt >> x >> y;
      if (opt == 1) cin >> z;
    }
    if (sub5::main()) return;
    if (sub1::main()) return;
    assert(false);
  }
}

int main() { lyre::main(); }
