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

const int kN = 1.0e5, kMaxN = kN + 5;
Array<bool, kMaxN> is_prime;
std::vector<int> prime, num;

void Sieve(int n) {
  std::fill_n(is_prime.begin() + 1, n, true), is_prime[1] = false;

  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) prime.emplace_back(i);

    for (int p : prime) {
      if (i * p > n) break;
      is_prime[i * p] = false;
      if (i % p == 0) break;
    }
  }
}

bool Check(int n) {
  std::vector<int> digit;
  while (n) digit.emplace_back(n % 10), n /= 10;
  std::reverse(digit.begin(), digit.end());
  int len = digit.size();

  for (int i = 1; i < (1 << len); ++i) {
    int val = 0;

    for (int j = 0; j < len; ++j) {
      if (i >> j & 1) val = val * 10 + digit[j];
    }

    if (is_prime[val]) return false;
  }

  return true;
}

void Init(int n) {
  Sieve(n);

  for (int i = 1; i <= n; ++i) {
    if (Check(i)) num.emplace_back(i);
  }
}

void Solve() {
  int l, r;
  cin >> l >> r;
  cout << std::upper_bound(num.begin(), num.end(), r) - std::lower_bound(num.begin(), num.end(), l) << "\n";
}

int Main() {
  base::OptimizeIO("prime.in", "prime.out");
  Init(kN);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
}

int main() { return Main(); }
