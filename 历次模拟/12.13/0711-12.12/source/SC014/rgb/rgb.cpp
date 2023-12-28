#include <bits/stdc++.h>
using namespace std;

const int N = 250 * 250 * 2 + 5;
const int M = 250 * 250 * 10;
const int Inf = 1e9;

int tot = 1, head[N], cur[N];
struct Edge {
  int nxt, v, w;
} e[M * 2];
inline void addEdge(int u, int v, int w) {
  e[++tot] = {head[u], v, w};
  head[u] = tot;
}
inline void add(int u, int v, int w) {
  // cerr << u << " " << v << " " << w << "\n";
  addEdge(u, v, w);
  addEdge(v, u, 0);
}

int s, t, dep[N];
int bfs() {
  fill(dep + s, dep + t + 1, 0);
  queue<int> q;
  q.push(s), dep[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (!dep[v] && w) {
        dep[v] = dep[u] + 1;
        q.push(v);
      }
    }
  }
  return dep[t];
}
int dfs(int u, int in) {
  if (u == t) return in;
  int out = 0;
  for (int i = cur[u]; i && in; i = e[i].nxt) {
    cur[u] = i;
    int v = e[i].v, w = e[i].w;
    if (dep[v] == dep[u] + 1 && w) {
      int res = dfs(v, min(in, w));
      in -= res, out += res;
      e[i].w -= res, e[i ^ 1].w += res;
    }
  }
  if (!out) dep[u] = 0;
  return out;
}
int dinic() {
  int res = 0;
  while (bfs()) {
    copy(head + s, head + t + 1, cur + s);
    res += dfs(s, Inf);
  }
  return res;
}

int r, g, b, m, n;
int eid(int i) {
  return n + 3 + i;
}
int rid() {
  return n + 1;
}
int gid() {
  return n + 2;
}
int bid() {
  return n + 3;
}
int id[M];
struct E {
  int u, v;
  char c;
} p[M];

int main() {
  freopen("rgb.in", "r", stdin);
  freopen("rgb.out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  cin >> r >> g >> b >> m, n = r + g + b + 1;
  if (n == 1) {
    cout << "YES\n";
    return 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    string str;
    cin >> u >> v >> str;
    p[i] = {u, v, str[0]};
  }
  map<pair<int, char>, int> mp;
  for (int _ = 1; _ <= m; _++) {
    int u = p[_].u, v = p[_].v;
    char c = p[_].c;
    if (u != 1) continue;
    if (mp.find({v, c}) != mp.end()) continue;
    if (c == 'r') {
      if (!r) continue;
      --r;
    }
    if (c == 'g') {
      if (!g) continue;
      --g;
    }
    if (c == 'b') {
      if (!b) continue;
      --b;
    }
    s = 0, t = n + m + 3 + 1;
    fill(head + s, head + t + 1, 0);
    tot = 1;
    for (int i = 1; i <= n; ++i) {
      if (i != v)
        add(i, t, 1);
    }
    add(s, rid(), r);
    add(s, gid(), g);
    add(s, bid(), b);
    int tar = v, bck = c;
    for (int i = 1; i <= m; i++) { 
      u = p[i].u, v = p[i].v, c = p[i].c;
      if (i == _) continue;
      if (u != 1 && u != tar) add(eid(i), u, 1);
      if (v != 1 && v != tar) add(eid(i), v, 1);
      int now = 0;
      if (c == 'r') now = rid();
      if (c == 'g') now = gid();
      if (c == 'b') now = bid();
      id[i] = tot + 1;
      add(now, eid(i), 1);
    }
    if (dinic() == n - 2) {
      cout << "YES\n";
      for (int i = 1; i <= m; ++i) {
        if (i == _) cout << 1;
        else cout << (e[id[i]].w ^ 1);
      }
      cout << "\n";
      return 0;
    }
    if (bck == 'r') ++r;
    if (bck == 'g') ++g;
    if (bck == 'b') ++b;
  }
  cout << "NO\n";
  return 0;
}