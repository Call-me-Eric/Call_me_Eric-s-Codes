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

const int kMaxN = 2.0e5 + 5;
int n, m;
Array<int, kMaxN> u, v, deg, fa, size, cnt;
Array<bool, kMaxN> vis;

int GetRoot(int x) { return x == fa[x] ? x : fa[x] = GetRoot(fa[x]); }

void Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y), ++cnt[x];
  if (x == y) return;
  if (size[x] > size[y]) std::swap(x, y);
  fa[x] = y, size[y] += size[x], cnt[y] += cnt[x], vis[y] |= vis[x];
}

int Main() {
  base::OptimizeIO("li.in", "li.out");
  cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    cin >> u[i] >> v[i];
    ++deg[u[i]], ++deg[v[i]];
  }

  for (int i = 1; i <= n; ++i) {
    if (deg[i] >= 4) cout << "-1\n", std::exit(0);
    if (deg[i] == 3) vis[i] = true;
  }

  std::iota(fa.begin() + 1, fa.begin() + n + 1, 1);
  std::fill_n(size.begin() + 1, n, 1);
  for (int i = 1; i <= m; ++i) Merge(u[i], v[i]);
  int64_t sum_chain = 0;
  int sum_cycle = 0;

  for (int i = 1; i <= n; ++i) {
    if (GetRoot(i) != i) continue;
    if (cnt[i] > size[i]) cout << "-1\n", std::exit(0);
    if (vis[i] && size[i] > 4) cout << "-1\n", std::exit(0);

    if (cnt[i] == size[i] || vis[i]) {
      sum_cycle += cnt[i];
    } else {
      sum_chain += int64_t{size[i]} * (size[i] + 1) / 2;
    }
  }


  if (sum_cycle) {
    cout << "1 " << sum_cycle << "\n";
  } else {
    cout << "0 " << sum_chain << "\n";
  }

  return 0;
}
}  // namespace

int main() { return Main(); }
