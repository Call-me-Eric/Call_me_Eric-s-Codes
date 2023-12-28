#include <bits/stdc++.h>

namespace {
using std::cin;
using std::cout;
using std::int64_t;
using std::size_t;

namespace base {
template <typename T, size_t ...sizes>
struct NestedArray {};

template <typename T, size_t size, size_t ...sizes>
struct NestedArray<T, size, sizes...> {
  using Type = std::array<typename NestedArray<T, sizes...>::Type, size>;
};

template <typename T>
struct NestedArray<T> {
  using Type = T;
};

template <typename T, size_t ...sizes>
using Array = typename NestedArray<T, sizes...>::Type;

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
}

void OptimizeIO(const std::string &input_file, const std::string &output_file) {
  static std::ifstream input_stream(input_file);
  static std::ofstream outpt_stream(output_file);
  cin.rdbuf(input_stream.rdbuf()), cout.rdbuf(outpt_stream.rdbuf());
  cin.tie(nullptr), cout.tie(nullptr);
}
}

using base::Array;

const int kMaxLen = 25;
int n, m, q, k, ans;
Array<int, kMaxLen> a, b;

int Distance(int len) {
  int ans = 0;
  for (int i = 1; i <= len; ++i) ans += std::abs(a[i] - b[i]);
  return ans;
}

void Dfs(int cur, int len) {
  while (len > m && a[len] == 0) --len;
  if (Distance(len) > k - cur + 1) return;

  if (cur > k) {
    ++ans;
    return;
  }

  for (int i = 1; i <= len + 1; ++i) {
    if (i == 1 || a[i - 1] > a[i]) ++a[i], Dfs(cur + 1, std::max(i, len)), --a[i];
    if (a[i] > a[i + 1]) --a[i], Dfs(cur + 1, len), ++a[i];
  }
}

int Main() {
  base::OptimizeIO("young.in", "young.out");
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  cin >> m;
  for (int i = 1; i <= m; ++i) cin >> b[i];
  cin >> q >> k;
  if (Distance(std::max(n, m)) > k) cout << "0\n", exit(0);
  int x = k & 1;
  for (int i = 1; i <= n; ++i) x ^= a[i] & 1;
  for (int i = 1; i <= m; ++i) x ^= b[i] & 1;
  if (x) cout << "0\n", exit(0);
  Dfs(1, std::max(n, m));
  cout << ans << "\n";
  return 0;
}
}

int main() { return Main(); }
