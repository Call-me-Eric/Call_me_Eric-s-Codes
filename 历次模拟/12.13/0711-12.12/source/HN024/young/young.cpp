#include <bits/stdc++.h>

using i64 = int64_t;

int ans;
std::vector<int> a, b;

void Dfs(int u) {
  if (u == 0) {
    auto tmp = a;
    while (tmp.size() && !tmp.back()) tmp.pop_back();
    return void(ans += (tmp == b));
  }
  for (int i = 0; i < a.size(); ++i) {
    if ((i != a.size() - 1 && a[i + 1] != a[i]) || (i == a.size() - 1 && a.back())) {
      --a[i], Dfs(u - 1), ++a[i];
    }
  }
  for (int i = 0; i < a.size(); ++i) {
    if (i == 0 || (i && a[i - 1] != a[i])) ++a[i], Dfs(u - 1), --a[i];
  }
  if (a.back() >= 1) a.emplace_back(1), Dfs(u - 1), a.pop_back();
}

auto main() -> int {
  freopen("young.in", "r", stdin);
  freopen("young.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int n, m;
  std::cin >> n;
  for (int i = 0, x; i < n; ++i) std::cin >> x, a.emplace_back(x);
  std::cin >> m;
  for (int i = 0, x; i < m; ++i) std::cin >> x, b.emplace_back(x);
  int q, k;
  std::cin >> q;
  while (q--) {
    std::cin >> k;
    ans = 0, Dfs(k);
    std::cout << ans << '\n';
  }
  return 0;
}