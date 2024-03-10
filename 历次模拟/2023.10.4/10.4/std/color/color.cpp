# define NDEBUG

#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdio>

using namespace std;
const int N = 200005;
int n, m;
vector<int> e[N];
map<int, int> color[N];
map<pair<int, int>, int> edge;
bool vis[N];
int father[N];

set<pair<int, int> > cycle;
map<int, int> cycle_color;
pair<int, int> special;

void dfs(int x, int fa) {
  vis[x] = 1;
  father[x] = fa;
  for (auto &y : e[x]) {
    if (!vis[y]) {
      dfs(y, x);
    } else if (y != fa) {
      if (cycle.empty()) {
        int z = x;
        while (z != y) {
          int xx = z, yy = father[z];
          if (xx > yy) swap(xx, yy);
          cycle.insert({xx, yy});
          z = father[z];
        }
        special = {min(x, y), max(x, y)};
        cycle.insert(special);
      }
    }
  }
}

inline void remove_color(map<int, int> &x, int c) {
  if (!--x[c]) {
    x.erase(c);
  }
}

void work() {
  scanf("%d%d", &n, &m);
  assert(3 <= n && n <= 200000);
  assert(1 <= m && m <= 100000);
  for (int i = 1; i <= n; ++i) {
    e[i].clear();
    color[i].clear();
    vis[i] = 0;
  }
  edge.clear();
  for (int i = 1; i <= n; ++i) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    assert(1 <= x && x <= n);
    assert(1 <= y && y <= n);
    assert(1 <= c && c <= n);
    if (x > y) swap(x, y);
    assert(x != y);
    assert(edge.count({x , y}) == 0);
    edge[{x, y}] = c;
    e[x].push_back(y);
    e[y].push_back(x);
  }

  cycle.clear();
  cycle_color.clear();
  dfs(1, 0);
  for (auto &&it : edge) {
    if (it.first != special) {
      int x = it.first.first;
      int y = it.first.second;
      int c = it.second;
      ++color[x][c];
      ++color[y][c];
      if (cycle.count(it.first)) {
        ++cycle_color[c];
      }
    }
  }

  int res = 1 - n;
  for (int i = 1; i <= n; ++i) {
    res += (int)color[i].size();
  }

  for (int i = 0; i < m; ++i) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    assert(1 <= x && x <= n);
    assert(1 <= y && y <= n);
    assert(1 <= c && c <= n);
    if (x > y) swap(x, y);
    assert(x != y);
    assert(edge.count({x , y}));
    auto e = make_pair(x, y);

    if (e == special) {
      edge[e] = c;
    } else {
      res -= (int)color[x].size();
      res -= (int)color[y].size();
      int rc = edge[e];
      remove_color(color[x], rc);
      remove_color(color[y], rc);
      if (cycle.count(e)) {
        remove_color(cycle_color, rc);
        ++cycle_color[c];
      }
      ++color[x][c];
      ++color[y][c];
      res += (int)color[x].size();
      res += (int)color[y].size();
      edge[e] = c;
    }
    int delta = 0;
    x = special.first;
    y = special.second;
    c = edge[special];
    if (!color[x].count(c) && !color[y].count(c)) {
      delta = 1;
    }
    if (color[x].count(c) && color[y].count(c)) {
      if (cycle_color.size() == 1 && c == cycle_color.begin()->first) {
      } else {
        delta = -1;
      }
    }
    printf("%d\n", res + delta);
  }
}

int main() {
  freopen("color.in", "r", stdin);
  freopen("color.out", "w", stdout);
  int T;T=1;
  while (T--) {
    work();
  }
}
