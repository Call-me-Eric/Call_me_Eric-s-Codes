#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;
using Equal = std::vector<int>;

const int kMaxN = 705, kMod = 998244353;
void Add(int& x, int y) {
  if ((x += y) >= kMod) x -= kMod;
}
auto Neg(int x) {
  if ((x = -x) < 0) x += kMod;
  return x;
}
auto Power(int a, int b, int p = kMod) {
  int r = 1;
  for (; b; b >>= 1, a = i64{a} * a % p) {
    if (b & 1) r = i64{r} * a % p;
  }
  return r;
}
auto Inv(int x, int p = kMod) { return Power(x, p - 2, p); }

int n, q;
std::vector<Equal> equal;
std::array<int, kMaxN> to, last;
auto GetEqual() {
  Equal e(n + 1);
  for (int &elem : e) std::cin >> elem;
  equal.emplace_back(e);
  return e;
}

struct Info {
  int l, r;
  std::vector<int> options;
};
std::array<Info, kMaxN * 4> tree;
void Build(int o, int l, int r) {
  tree[o].l = l, tree[o].r = r, tree[o].options.clear();
  if (l == r) return;
  int mid = (l + r) >> 1;
  Build(o * 2, l, mid), Build(o * 2 + 1, mid + 1, r);
}
void Add(int o, int x, int y, int id) {
  int l = tree[o].l, r = tree[o].r;
  if (x <= l && r <= y) return void(tree[o].options.emplace_back(id));
  if (x > y || x > r || l > y) return;
  Add(o * 2, x, y, id), Add(o * 2 + 1, x, y, id);
}

int cnt_no, cnt_many;
std::array<std::vector<int>, kMaxN> cur;
std::array<int, kMaxN * 2> insert_to;
std::array<bool, kMaxN * 2> is_no, is_many;
void Insert(int id) {
  auto eq = equal[id];
  is_no[id] = is_many[id] = false;
  for (int i = 0; i < n; ++i) {
    if (!eq[i]) continue;
    if (cur[i].empty()) {
      insert_to[id] = i;
      cur[i] = eq;
      return;
    }
    int rate = i64{eq[i]} * Inv(cur[i][i]) % kMod;
    for (int j = i; j <= n; ++j) {
      Add(eq[j], Neg(i64{rate} * cur[i][j] % kMod));
    }
  }
  if (eq.back()) ++cnt_no, is_no[id] = true;
  if (!eq.back()) ++cnt_many, is_many[id] = true;
}
void Pop(int id) {
  if (is_no[id]) {
    is_no[id] = false;
    --cnt_no;
    return;
  }
  if (is_many[id]) {
    is_many[id] = false;
    --cnt_many;
    return;
  }
  cur[insert_to[id]].clear();
}
void Solve(int o) {
  for (int id : tree[o].options) Insert(id);

  int l = tree[o].l, r = tree[o].r;
  if (l == r) {
    if (cnt_no) return void(std::cout << "No\n");
    if (cnt_many) return void(std::cout << "Many\n");
    std::vector<int> ret(n);
    for (int i = n - 1; ~i; --i) {
      ret[i] = cur[i].back();
      for (int j = i + 1; j < n; ++j) {
        Add(ret[i], Neg(i64{ret[j]} * cur[i][j] % kMod));
      }
      ret[i] = i64{ret[i]} * Inv(cur[i][i]) % kMod;
    }
    for (int i = 0; i < n; ++i) std::cout << ret[i] << "\n "[i < n - 1];
  } else {
    Solve(o * 2), Solve(o * 2 + 1);
  }

  std::reverse(ALL(tree[o].options));
  for (int id : tree[o].options) Pop(id);
  std::reverse(ALL(tree[o].options));
}

auto main() -> int {
  freopen("eq.in", "r", stdin);
  freopen("eq.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    auto e = GetEqual();
    last[i] = 0, to[i] = equal.size() - 1;
  }
  Build(1, 0, q);
  for (int i = 1, z; i <= q; ++i) {
    std::cin >> z;
    auto e = GetEqual();
    Add(1, last[z], i - 1, to[z]);
    last[z] = i, to[z] = equal.size() - 1;
  }
  for (int i = 1; i <= n; ++i) Add(1, last[i], q, to[i]);

  Solve(1);

  return 0;
}