# include <cstdio>
# include <vector>
# include <queue>
# include <algorithm>
# include <functional>

# define int long long

void Sum() {

  int n, m;
  scanf("%lld %lld", &n, &m);
  
  std::vector<int> sum(n + 1);
  for (int i = 1; i <= n; ++i) scanf("%lld", &sum[i]);
  for (int i = 1; i <= n; ++i) sum[i] += sum[i - 1];

  for (int i = 1; i <= m; ++i) {
    int l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", sum[r] - sum[l - 1]);
  }
}

void diameter() {

  int n;
  scanf("%lld", &n);

  std::vector<std::vector<std::pair<int, int> > > G(n + 1);

  for (int i = 1; i < n; ++i) {
    int x, y, val;
    scanf("%lld %lld %lld", &x, &y, &val);
    G[x].emplace_back(y, val), G[y].emplace_back(x, val);
  }

  int mx = 0, s;

  std::function<void(int, int, int)> dfs1 = [&](int u, int father, int dis) {
    if (dis > mx) mx = dis, s = u;
    for (auto [k, val] : G[u]) if (k != father) {
      dfs1(k, u, dis + val);
    }
  };
  dfs1(1, 0, 0);

  mx = 0;

  std::function<void(int, int, int)> dfs2 = [&](int u, int father, int dis) {
    if (dis > mx) mx = dis;
    for (auto [k, val] : G[u]) if (k != father) {
      dfs2(k, u, dis + val);
    }
  };
  dfs2(s, 0, 0);

  printf("%lld\n", mx);
}

void shortest_path() {

  int n, m;
  scanf("%lld %lld", &n, &m);

  std::vector<std::vector<std::pair<int, int> > > G(n + 1);

  for (int i = 1; i <= m; ++i) {
    int x, y, val;
    scanf("%lld %lld %lld", &x, &y, &val);
    G[x].emplace_back(y, val), G[y].emplace_back(x, val);
  }

  std::vector<int> dis(n + 1, 1e18);
  std::vector<bool> vis(n + 1, false);

  std::queue<int> q;
  q.push(1), dis[1] = 0, vis[1] = true;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    vis[u] = false;
    for (auto [k, val] : G[u]) {
      if (dis[k] > dis[u] + val) {
        dis[k] = dis[u] + val;
        if (!vis[k]) vis[k] = true, q.push(k);
      }
    }
  }

  printf("%lld\n", dis[n]);
}

signed main() {

  freopen("crack.in", "r", stdin);
  freopen("crack.out", "w", stdout);

  int T;
  scanf("%lld", &T);

  switch (T) {
    case 1: puts("oeis"); break;
    case 2: puts("oeis"); break;
    case 3: Sum(); break;
    case 4: puts(">_<"); break;
    case 5: diameter(); break;
    case 6: diameter(); break;
    case 7: shortest_path(); break;
    case 8: shortest_path(); break;
    case 9: puts(">_<"); break;
    case 10: puts(">_<"); break;
    default: puts(">_<");
  }

  return 0;
}