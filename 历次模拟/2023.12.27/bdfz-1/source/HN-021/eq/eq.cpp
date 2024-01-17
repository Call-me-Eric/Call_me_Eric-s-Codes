#include <bits/stdc++.h>

namespace {
using std::cin;
using std::cout;
using std::int64_t;
using std::size_t;

namespace base {
template <typename T, size_t... sizes>
struct NestedArray {};

template <typename T, size_t size, size_t... sizes>
struct NestedArray<T, size, sizes...> {
  using Type = std::array<typename NestedArray<T, sizes...>::Type, size>;
};

template <typename T>
struct NestedArray<T> {
  using Type = T;
};

template <typename T, size_t... sizes>
using Array = typename NestedArray<T, sizes...>::Type;

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
}

void OptimizeIO(const std::string &input_file, const std::string &output_file) {
  static std::ifstream input_stream(input_file);
  static std::ofstream output_stream(output_file);
  cin.rdbuf(input_stream.rdbuf()), cout.rdbuf(output_stream.rdbuf());
  cin.tie(nullptr), cout.tie(nullptr);
}
}  // namespace base

using base::Array;

const int kMod = 998244353;

namespace mod {
inline void Sub(int &a, int b) {
  a -= b;
  if (a < 0) a += kMod;
}

inline void Mul(int &a, int b) { a = int64_t{a} * b % kMod; }

inline int Prod(int a, int b) { return int64_t{a} * b % kMod; }

int Pow(int a, int b) {
  int ans = 1, prod = a;

  while (b) {
    if (b & 1) Mul(ans, prod);
    Mul(prod, prod), b >>= 1;
  }

  return ans;
}

inline int Inv(int a) { return Pow(a, kMod - 2); }
}

const int kMaxN = 705, kMax2N = kMaxN * 2, kMax4N = kMaxN * 4;
int n, m, tot;
Array<int, kMaxN> id, last;

struct Vector {
  Array<int, kMaxN> a;
};

inline Vector& operator*=(Vector &u, int k) {
  for (int i = 1; i <= n + 1; ++i) mod::Mul(u.a[i], k);
  return u;
}

inline Vector operator*(Vector u, int k) { return u *= k; }

inline Vector& operator-=(Vector &u, const Vector &v) {
  for (int i = 1; i <= n + 1; ++i) mod::Sub(u.a[i], v.a[i]);
  return u;
}

Array<Vector, kMax2N> c;

class LinearBasis {
 public:
  int Insert(Vector u);
  void Solve();
  void Remove(int x) { base_[x].a[x] = 0; }

 private:
  Array<Vector, kMaxN> base_;
  Array<int, kMaxN> inv_, x_;
};

int LinearBasis::Insert(Vector u) {
  for (int i = 1; i <= n; ++i) {
    if (!u.a[i]) continue;

    if (!base_[i].a[i]) {
      base_[i] = u, inv_[i] = mod::Inv(u.a[i]);
      return i;
    }

    u -= base_[i] * mod::Prod(inv_[i], u.a[i]);
  }

  return u.a[n + 1] ? -1 : 0;
}

void LinearBasis::Solve() {
  for (int i = n; i >= 1; --i) {
    int val = base_[i].a[n + 1];
    for (int j = i + 1; j <= n; ++j) mod::Sub(val, mod::Prod(x_[j], base_[i].a[j]));
    x_[i] = mod::Prod(val, inv_[i]);
  }

  for (int i = 1; i <= n; ++i) cout << x_[i] << " ";
  cout << "\n";
}

class SegmentTree {
 public:
  void Insert(int l, int r, int val) { Insert(1, 0, m, l, r, val); }
  void Query() { Query(1, 0, m, true); }

 private:
  void Insert(int p, int l, int r, int L, int R, int val);
  void Query(int p, int l, int r, bool valid);
  Array<std::vector<int>, kMax4N> id_;
  LinearBasis linear_basis;
};

void SegmentTree::Insert(int p, int l, int r, int L, int R, int val) {
  if (L <= l && R >= r) {
    id_[p].emplace_back(val);
    return;
  }

  int mid = (l + r) >> 1;
  if (L <= mid) Insert(p << 1, l, mid, L, R, val);
  if (R > mid) Insert(p << 1 | 1, mid + 1, r, L, R, val);
}

void SegmentTree::Query(int p, int l, int r, bool valid) {
  std::vector<int> xs;

  for (int i : id_[p]) {
    int x = linear_basis.Insert(c[i]);

    if (x == -1) {
      for (int i = l; i <= r; ++i) cout << "No\n";
      return;
    }

    if (x == 0) {
      valid = false;
    } else {
      xs.emplace_back(x);
    }
  }

  if (l == r) {
    if (valid) {
      linear_basis.Solve();
    } else {
      cout << "Many\n";
    }
  } else {
    int mid = (l + r) >> 1;
    Query(p << 1, l, mid, valid), Query(p << 1 | 1, mid + 1, r, valid);
  }

  for (int x : xs) linear_basis.Remove(x);
}

SegmentTree tree;

int AddEquation() {
  ++tot;
  for (int i = 1; i <= n + 1; ++i) cin >> c[tot].a[i];
  return tot;
}

int Main() {
  base::OptimizeIO("eq.in", "eq.out");
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) id[i] = AddEquation(), last[i] = 0;

  for (int i = 1; i <= m; ++i) {
    int x;
    cin >> x;
    tree.Insert(last[x], i - 1, id[x]);
    id[x] = AddEquation(), last[x] = i;
  }

  for (int i = 1; i <= n; ++i) tree.Insert(last[i], m, id[i]);
  tree.Query();
  return 0;
}
}  // namespace

int main() { return Main(); }
