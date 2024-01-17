# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  ifstream  cin("subway.in");
  ofstream cout("subway.out");
  constexpr size_t N(600), K(8);
  vector<pair<int, long long>> G[N][K];
  long long a[N][K], b[N][K];
  long long dis[N][1 << K][K];
  int n, k;
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int t(0); t < k; ++t) {
      for (int i(1); i <= n; ++i)
        cin >> a[i][t];
      for (int i(1); i <= n; ++i)
        cin >> b[i][t];
      int m; cin >> m;
      for (int i(0); i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][t].emplace_back(v, w);
        G[v][t].emplace_back(u, w);
      }
    }
    using node = tuple<long long, int, int, int>;
    priority_queue<node, vector<node>, greater<node>> heap;
    memset(dis, 0x3f, sizeof dis);
    for (int i(0); i < k; ++i) {
      dis[1][1 << i][i] = a[1][i];
      heap.emplace(a[1][i], 1, 1 << i, i);
    }
    while (!heap.empty()) {
      auto const d(get<0>(heap.top()));
      auto const u(get<1>(heap.top()));
      auto const s(get<2>(heap.top()));
      auto const t(get<3>(heap.top()));
      heap.pop();
      if (d != dis[u][s][t]) continue;
      for (int i(0); i < k; ++i) {
        for (auto const j : G[u][i]) {
          auto v(j.first), nxt(s);
          auto w(j.second), cost(w);
          if (i != t && s >> i & 1) continue;
          if (i != t && u == 1) continue;
          if (i != t && ~s >> i & 1) {
            cost += b[u][t] + a[u][i];
            nxt |= 1 << i;
          }
          if (dis[v][nxt][i] > dis[u][s][t] + cost) {
            dis[v][nxt][i] = dis[u][s][t] + cost;
            heap.emplace(dis[v][nxt][i], v, nxt, i);
          }
        }
      }
    }
    auto ans(LLONG_MAX);
    for (int i(0); i < k; ++i) {
      auto res(LLONG_MAX);
      for (int j(0); j != 1 << k; ++j)
        res = min(res, dis[n][j][i]);
      ans = min(ans, res + b[n][i]);
    }
    cout << ans << endl;
  }
}

int main() { lyre::main(); }
