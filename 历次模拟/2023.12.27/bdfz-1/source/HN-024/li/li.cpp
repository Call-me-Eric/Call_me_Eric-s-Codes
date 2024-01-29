#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;

const int kMaxN = 2E5 + 5;

int n, m;
std::array<std::vector<int>, kMaxN> g;
std::array<int, kMaxN> deg;
std::array<bool, kMaxN> vis;
std::vector<int> cur;

void Dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  cur.emplace_back(u);
  for (int v : g[u]) Dfs(v);
}

auto main() -> int {
  freopen("li.in", "r", stdin);
  freopen("li.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  
  std::cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    ++deg[u], ++deg[v];
  }

  i64 ans_chain = 0, ans_circle = 0;
  bool exist = false;
  for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    cur.clear(), Dfs(i);
    if (cur.size() == 1) {
      ++ans_chain;
      continue;
    }
    int cnt_2 = 0, cnt_1 = 0;
    for (int t : cur) cnt_2 += (deg[t] == 2), cnt_1 += (deg[t] == 1);
    if (cnt_1 == 2 && cnt_2 == cur.size() - 2) {
      ans_chain += i64{cur.size() + 1} * cur.size() / 2;
      continue;
    } 
    bool all = true;
    for (int t : cur) all &= (deg[t] == 2);
    if (all) {
      exist = true;
      ans_circle += cur.size();
      continue;
    }
    if (cur.size() != 4) {
      return std::cout << "-1\n", 0;
    }
    bool found = false;
    for (int i = 0; i < 4; ++i) {
      std::set<int> to;
      for (int e : g[cur[i]]) to.emplace(e);
      to.erase(cur[i]);
      bool all = (to.size() == 3);
      if (all == false) continue;
      for (int j = 0; j < 4; ++j) {
        if (j == i) continue;
        std::set<int> to;
        for (int e : g[cur[j]]) to.emplace(e);
        all &= (to.size() == 1 && *begin(to) == cur[i]);
      }
      if (all) {
        found = exist = true, ans_circle += 3;
      }
    }
    if (!found) return std::cout << "-1\n", 0;
  }
  if (exist) {
    std::cout << "1 " << ans_circle << '\n';
  } else {
    std::cout << "0 " << ans_chain << '\n';
  }
  return 0;
}