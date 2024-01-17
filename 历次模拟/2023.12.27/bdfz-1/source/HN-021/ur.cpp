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

int Main() {
  base::OptimizeIO("ur.in", "ur.out");
  int n;
  cin >> n;
  cout << std::string(n, '0')  << "\n";
  return 0;
}
}  // namespace

int main() { return Main(); }
