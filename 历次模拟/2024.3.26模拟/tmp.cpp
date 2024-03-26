# include <bits/stdc++.h>

using namespace std;

namespace lyre {
  ifstream  cin("smart.in");
  ofstream cout("smart.out");
  constexpr int nmax(100'100);
  int n, m, a[nmax];
  struct info {
    long mx, mn, ans;
    int mxp, mnp, al, ar;
    constexpr info() : mx(), mn(), ans(), mxp(), mnp(), al(), ar() {}
    constexpr info operator+(info const &b) const {
      info r;
      if (mx > b.mx) r.mx = mx, r.mxp = mxp;
      else r.mx = b.mx, r.mxp = b.mxp;
      if (mn < b.mn) r.mn = mn, r.mnp = mnp;
      else r.mn = b.mn, r.mnp = b.mnp;
      if (ans > b.ans) r.ans = ans, r.al = al, r.ar = ar;
      else r.ans = b.ans, r.al = b.al, r.ar = b.ar;
      if (mx - b.mn > ans) r.ans = mx - b.mn, r.al = mxp, r.ar = b.mnp;
      return r;
    }
  };
  class segment_tree {
    info tr[4 * nmax];
    long tag[4 * nmax];
    void assign(int u, int k) {
      tr[u].mx += k, tr[u].mn += k;
      tag[u] += k;
    }
    void down(int u) {
      if (!tag[u]) return;
      assign(u << 1, tag[u]);
      assign(u << 1 | 1, tag[u]);
      tag[u] = 0;
    }
    public:
    void build(int u, int l, int r) {
      if (l == r) {
        tr[u].mx = tr[u].mn = a[l];
        tr[u].mxp = tr[u].mnp = l;
        tr[u].al = tr[u].ar = l;
        tr[u].ans = 0;
        return;
      }
      auto mid((l + r) / 2);
      build(u << 1, l, mid);
      build(u << 1 | 1, mid + 1, r);
      tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }
    void add(int u, int l, int r, int x, int y, int k) {
      if (l == x && r == y) return assign(u, k);
      auto mid((l + r) / 2);
      down(u);
      if (y <= mid) {
        add(u << 1, l, mid, x, y, k);
      } else if (x > mid) {
        add(u << 1 | 1, mid + 1, r, x, y, k);
      } else {
        add(u << 1, l, mid, x, mid, k);
        add(u << 1 | 1, mid + 1, r, mid + 1, y, k);
      }
      tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }
    info query(int u, int l, int r, int x, int y) {
      if (l == x && r == y) return tr[u];
      auto mid((l + r) / 2);
      down(u);
      if (y <= mid) {
        return query(u << 1, l, mid, x, y);
      } else if (x > mid) {
        return query(u << 1 | 1, mid + 1, r, x, y);
      } else {
        return query(u << 1, l, mid, x, mid)
             + query(u << 1 | 1, mid + 1, r, mid + 1, y);
      }
    }
  } seg;
  struct node {
    int al, ar, bl, br; long val;
    node(int a, int b, int c, int d) : al(a), ar(b), bl(c), br(d) {
      if (ar <= bl) val = seg.query(1, 1, n, al, ar).mx - seg.query(1, 1, n, bl, br).mn;
      else val = seg.query(1, 1, n, al, ar).ans;
    }
    constexpr bool operator<(node const &b) const { return val < b.val; }
  };
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i(1); i <= n; ++i) cin >> a[i];
    seg.build(1, 1, n);
    for (int i(1); i <= m; ++i) {
      int o, l, r, k;
      cin >> o >> l >> r >> k;
      if (o == 1) {
        seg.add(1, 1, n, l, r, k);
      } else {
        auto ans(0l);
        priority_queue<node> heap;
        heap.emplace(l, r, l, r);
        for (int j(1); j <= k; ++j) {
          auto u(heap.top());
          heap.pop(), ans += u.val;
          if (u.ar < u.bl) {
            auto s(seg.query(1, 1, n, u.al, u.ar));
            auto t(seg.query(1, 1, n, u.bl, u.br));
            if (u.al < s.mxp) heap.emplace(u.al, s.mxp - 1, u.bl, u.br);
            if (s.mxp < u.ar) heap.emplace(s.mxp + 1, u.ar, u.bl, u.br);
            if (u.bl < t.mnp) heap.emplace(s.mxp, s.mxp, u.bl, t.mnp - 1);
            if (t.mnp < u.br) heap.emplace(s.mxp, s.mxp, t.mnp + 1, u.br);
          } else {
            auto t(seg.query(1, 1, n, u.al, u.ar));
            auto x(t.al), y(t.ar);
            if (x > u.al) heap.emplace(u.al, x - 1, u.al, x - 1);
            if (x > u.al) heap.emplace(u.al, x - 1, x, u.ar);
            if (x != y) heap.emplace(x, x, x, x);
            if (x + 1 <= y - 1) heap.emplace(x, x, x + 1, y - 1);
            if (y < u.ar) heap.emplace(x, x, y + 1, u.ar);
            if (x < u.ar) heap.emplace(x + 1, u.ar, x + 1, u.ar);
          }
        }
        cout << ans << '\n';
      }
    }
  }
}

int main() { lyre::main(); }