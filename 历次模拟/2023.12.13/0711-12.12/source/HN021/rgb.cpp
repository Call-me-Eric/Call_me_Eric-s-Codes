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

const int kMaxN = 255, kMaxM = kMaxN * kMaxN / 2;
int n, m;
Array<int, 3> a, num;
Array<int, kMaxN> fa, go, edge_id, dep;
Array<int, kMaxM> u, v, w;
Array<bool, kMaxM> use;
Array<int, kMaxN, kMaxN> lca;
Array<std::vector<std::pair<int, int>>, kMaxN> edge;

int GetRoot(int x) { return x == fa[x] ? x : fa[x] = GetRoot(fa[x]); }

void AddEdge(int type) {
  for (int i = 1; i <= m; ++i) {
    if (w[i] != type) continue;
    int x = GetRoot(u[i]), y = GetRoot(v[i]);
    if (x != y) fa[x] = y, ++num[type], use[i] = true;
  }
}

void AddEdge() {
  for (int i = 1; i <= n; ++i) edge[i].clear();

  for (int i = 1; i <= m; ++i) {
    if (use[i]) {
      edge[u[i]].emplace_back(v[i], i), edge[v[i]].emplace_back(u[i], i);
    }
  }
}

std::vector<int> Dfs(int u, int fa, int type) {
  dep[u] = dep[fa] + 1;
  std::vector<int> ver = {u};

  for (const auto &e : edge[u]) {
    int v = e.first, id = e.second;
    if (v == fa) continue;
    edge_id[v] = id, go[v] = (w[id] == type ? v : go[u]);
    auto tmp = Dfs(v, u, type);

    for (int x : ver) {
      for (int y : tmp) lca[x][y] = lca[y][x] = u;
    }

    ver.insert(ver.end(), tmp.begin(), tmp.end());
  }

  return ver;
}

void Work(int type, int ban = -1) {
  while (num[type] > a[type]) {
    AddEdge(), Dfs(1, 0, type);
    bool found = false;

    for (int i = 1; i <= m; ++i) {
      if (w[i] == type || w[i] == ban || use[i]) continue;
      int l = lca[u[i]][v[i]], x = go[u[i]], y = go[v[i]];

      if (dep[x] > dep[l]) {
        found = true, use[edge_id[x]] = false, use[i] = true;
        --num[type], ++num[w[i]];
        break;
      }

      if (dep[y] > dep[l]) {
        found = true, use[edge_id[y]] = false, use[i] = true;
        --num[type], ++num[w[i]];
        break;
      }
    }

    if (!found) cout << "NO\n", exit(0);
  }
}

int Main() {
  base::OptimizeIO("rgb.in", "rgb.out");
  cin >> a[0] >> a[1] >> a[2] >> m, n = a[0] + a[1] + a[2] + 1;

  for (int i = 1; i <= m; ++i) {
    char c;
    cin >> u[i] >> v[i] >> c, w[i] = (c == 'r' ? 0 : c == 'g' ? 1 : 2);
  }

  std::iota(fa.begin() + 1, fa.begin() + n + 1, 1);
  AddEdge(0);
  if (num[0] < a[0]) cout << "NO\n", exit(0);
  AddEdge(1), AddEdge(2);
  Work(0), Work(1, 0), Work(2, 0);
  cout << "YES\n";
  for (int i = 1; i <= m; ++i) cout << use[i];
  cout << "\n";
  return 0;
}
}

int main() { return Main(); }
