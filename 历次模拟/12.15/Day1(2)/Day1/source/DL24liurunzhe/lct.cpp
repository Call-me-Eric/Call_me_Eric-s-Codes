# include <cstdio>
# include <vector>
# include <algorithm>
# include <functional>

int main() {

  freopen("lct.in", "r", stdin);
  freopen("lct.out", "w", stdout);

  int n, m;
  scanf("%d %d", &n, &m);
 
  std::vector<std::vector<int> > vec(n + 1);

  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    vec[std::minmax(x, y).second].push_back(std::minmax(x, y).first);
  }

  std::vector<std::vector<std::pair<int, int> > > query(n + 1);

  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    query[y].emplace_back(x, i);
  }

  std::vector<int> tr(n + 1);

  auto add = [&](int x, int val) {
    for (; x <= n; x += x & -x)
      tr[x] += val;
  };

  auto sum = [&](int x) {
    int res = 0;
    for (; x; x -= x & -x)
      res += tr[x]; return res;
  };

  std::vector<int> ans(m + 1);

  for (int i = 1; i <= n; ++i) {
    for (int k : vec[i]) add(k, 1);
    for (auto k : query[i]) 
      ans[k.second] = i - k.first + 1 - sum(i) + sum(k.first - 1);
  }

  for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);

  return 0;
}