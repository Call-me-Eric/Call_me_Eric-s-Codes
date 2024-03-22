#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128;
using u128 = unsigned __int128;
template <typename T>
void chkmax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
void chkmin(T &x, const T &y) {
  if (y < x) x = y;
}
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
struct matrix {
  ll d[2][2];
  ll *operator[](int x) { return d[x]; }
  const ll *operator[](int x) const { return d[x]; }
};
matrix operator*(const matrix &x, const matrix &y) {
  matrix z;
  memset(z.d, 0x3f, sizeof(z.d));
  for (int i = 0; i < 2; ++i) {
    for (int k = 0; k < 2; ++k) {
      if (x[i][k] == INFLL) continue;
      for (int j = 0; j < 2; ++j) chkmin(z[i][j], x[i][k] + y[k][j]);
    }
  }
  return z;
}
constexpr int MAXN = 3e5 + 10;
int n, q, a[MAXN], mx[19][MAXN], tot, gol[MAXN], gor[MAXN];
int pos[MAXN], anc[MAXN * 2][20], dep[MAXN * 2], id[MAXN * 2];
matrix st_out[MAXN], st_in[MAXN], out[MAXN * 2][20], in[MAXN * 2][20];
vector<int> g[MAXN * 2];
vector<ll> prfl[MAXN * 2], prfr[MAXN * 2], sufl[MAXN * 2], sufr[MAXN * 2];
pair<int, int> rg[MAXN * 2];
bool cmp(int x, int y) { return a[x] < a[y]; }
int get_max(int l, int r) {
  int k = __lg(r - l + 1);
  return max(mx[k][l], mx[k][r - (1 << k) + 1], cmp);
}
ll go(int u, int v) {
  if (!u || !v || u == n + 1 || v == n + 1) return INFLL;
  return u < v ? gor[u] : gol[u];
}
void build(int u, int l, int r) {
  rg[u] = {l, r};
  if (l + 1 == r) {
    if (l) {
      pos[l] = u;
      st_out[l] = {{{0, go(l, r)}, {INFLL, INFLL}}};
      st_in[l] = {{{0, go(r, l)}, {INFLL, INFLL}}};
    }
    if (r != n + 1) {
      pos[r] = u;
      st_out[r] = {{{go(r, l), 0}, {INFLL, INFLL}}};
      st_in[r] = {{{go(l, r), 0}, {INFLL, INFLL}}};
    }
    return;
  }
  int st = get_max(l + 1, r - 1);
  g[++tot].clear();
  g[u].emplace_back(tot);
  build(tot, l, st);
  int p = st;
  for (int np; p + 1 != r; p = np) {
    np = get_max(p + 1, r - 1);
    if (a[np] != a[st]) break;
    g[++tot].clear();
    g[u].emplace_back(tot);
    build(tot, p, np);
  }
  g[++tot].clear();
  g[u].emplace_back(tot);
  build(tot, p, r);
}
void dfs(int u) {
  if (g[u].empty()) return;
  prfl[u].resize(g[u].size());
  prfr[u].resize(g[u].size());
  prfl[u][0] = prfr[u][0] = 0;
  for (int i = 1; i < (int)g[u].size(); ++i) {
    prfl[u][i] = prfl[u][i - 1] + go(rg[g[u][i - 1]].second, rg[g[u][i - 1]].first);
    prfr[u][i] = prfr[u][i - 1] + go(rg[g[u][i - 1]].first, rg[g[u][i - 1]].second);
  }
  sufl[u].resize(g[u].size());
  sufr[u].resize(g[u].size());
  sufl[u][g[u].size() - 1] = sufr[u][g[u].size() - 1] = 0;
  for (int i = g[u].size() - 2; i >= 0; --i) {
    sufl[u][i] = sufl[u][i + 1] + go(rg[g[u][i + 1]].second, rg[g[u][i + 1]].first);
    sufr[u][i] = sufr[u][i + 1] + go(rg[g[u][i + 1]].first, rg[g[u][i + 1]].second);
  }
  for (int t = 0; t < (int)g[u].size(); ++t) {
    int v = g[u][t];
    id[v] = t;
    dep[v] = dep[u] + 1;
    anc[v][0] = u;
    out[v][0] = {{{prfl[u][t], prfl[u][t] + go(rg[u].first, rg[u].second)},
                  {sufr[u][t] + go(rg[u].second, rg[u].first), sufr[u][t]}}};
    in[v][0] = {{{prfr[u][t], prfr[u][t] + go(rg[u].second, rg[u].first)},
                 {sufl[u][t] + go(rg[u].first, rg[u].second), sufl[u][t]}}};
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        chkmin(out[v][0][i][j], INFLL);
        chkmin(in[v][0][i][j], INFLL);
      }
    }
    for (int i = 1; i < 20; ++i) {
      anc[v][i] = anc[anc[v][i - 1]][i - 1];
      in[v][i] = in[v][i - 1] * in[anc[v][i - 1]][i - 1];
      out[v][i] = out[v][i - 1] * out[anc[v][i - 1]][i - 1];
    }
    dfs(v);
  }
}
int get_lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = 19; i >= 0; --i)
    if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
  if (u == v) return u;
  for (int i = 19; i >= 0; --i) {
    if (anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  }
  return anc[u][0];
}
int main() {
  freopen("railway.in", "r", stdin);
  freopen("railway.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int cas;
  cin >> cas;
  while (cas--) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> gol[i] >> gor[i];
    if (n == 1) {
      for (int i = 1; i <= q; ++i) cout << "0\n";
      continue;
    }
    iota(mx[0] + 1, mx[0] + n + 1, 1);
    for (int i = 1; 1 << i <= n; ++i) {
      for (int j = 1; j + (1 << i) - 1 <= n; ++j)
        mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))], cmp);
    }
    g[tot = 1].clear();
    build(1, 0, n + 1);
    dep[1] = 1;
    dfs(1);
    while (q--) {
      int x, y;
      cin >> x >> y;
      int u = pos[x], v = pos[y];
      if (u == v) {
        cout << min(st_out[x][0][0] + st_in[y][0][0], st_out[x][0][1] + st_in[y][0][1]) << "\n";
        continue;
      }
      int t = get_lca(u, v);
      assert(u != t && v != t);
      matrix mu = st_out[x], mv = st_in[y];
      // cout << u << " " << v << " " << t << " QAQ\n";
      for (int i = 19; i >= 0; --i) {
        if (dep[anc[u][i]] > dep[t]) {
          mu = mu * out[u][i];
          u = anc[u][i];
        }
      }
      for (int i = 19; i >= 0; --i) {
        if (dep[anc[v][i]] > dep[t]) {
          mv = mv * in[v][i];
          v = anc[v][i];
        }
      }
      // cout << mu[0][0] << " " << mu[0][1] << "\n";
      // cout << mv[0][0] << " " << mv[0][1] << "\n";
      u = id[u];
      v = id[v];
      if (u < v) {
        cout << (ll)min((i128)mu[0][1] + mv[0][0] + prfr[t][v] - prfr[t][u + 1],
                        (i128)mu[0][0] + mv[0][1] + prfl[t][u] + sufl[t][v] + go(rg[t].first, rg[t].second))
             << "\n";
      } else {
        cout << (ll)min((i128)mu[0][0] + mv[0][1] + prfl[t][u] - prfl[t][v + 1], 
                        (i128)mu[0][1] + mv[0][0] + sufr[t][u] + prfr[t][v] + go(rg[t].second, rg[t].first))
             << "\n";
      }
    }
  }
  return 0;
}