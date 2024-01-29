# include <cstdio>
# include <vector>
# include <string>
# include <iostream>
# include <algorithm>
# include <functional>

# define int long long

constexpr int MAXN = 1e6 + 5, MOD = 998244353;

int ed[MAXN << 1];
int trie[MAXN << 1][26], totN;

std::vector<int> node[MAXN << 1];

void extend(std::string s, int id) {
  int p = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (!trie[p][ s[i] - 'a' ]) 
      trie[p][ s[i] - 'a' ] = ++totN;
    p = trie[p][ s[i] - 'a' ], node[id][i] = p;
  }
  ed[p] ++;
}

int fail[MAXN << 1];
std::vector<int> G[MAXN << 1];

int dfn[MAXN << 1], siz[MAXN << 1], cnt;

void build() {
  std::vector<int> q(MAXN << 1);
  auto hd = q.begin(), tl = q.begin();
  
  for (int i = 0; i < 26; ++i) {
    fail[ trie[0][i] ] = 0;
    if (trie[0][i]) *tl ++ = trie[0][i];
  }

  while (hd != tl) {
    int u = *hd ++;
    for (int i = 0; i < 26; ++i) {
      if (trie[u][i]) {
        fail[ trie[u][i] ] = trie[ fail[u] ][i];
        *tl ++ = trie[u][i];
      } else {
        trie[u][i] = trie[ fail[u] ][i];
      }
    }
  }

  for (int i = 1; i <= totN; ++i) {
    G[ fail[i] ].push_back(i);
  }

  std::function<void(int)> dfs = [&](int u) {
    dfn[u] = ++cnt, siz[u] = 1;
    for (int k : G[u]) {
      dfs(k);
      ed[u] += ed[k], siz[u] += siz[k];
    }
  };
  dfs(0);
}

signed main() {

  freopen("unpredictable.in", "r", stdin);
  freopen("unpredictable.out", "w", stdout);

  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::string> s(n + 1);

  std::vector<std::vector<int> > vec(n + 1); 

  for (int i = 1; i <= n; ++i) {
    std::cin >> s[i];
    vec[i].resize(s[i].size());
    node[i].resize(s[i].size());
    extend(s[i], i);
    for (int j = 0; j < s[i].size(); ++j) {
      std::cin >> vec[i][j];
    }
  }
  build();

  int ans = 0;

  std::vector<int> tr(MAXN + 1);

  auto add = [&](int x, int val) {
    for (; x <= MAXN; x += x & -x)
      tr[x] += val;
  };

  auto query = [&](int x) {
    if (x < 0) return 0LL;
    int res = 0;
    for (; x; x -= x & -x)
      res += tr[x]; return res;
  };

  auto Q = [&](int l, int r) {
    return query(r) - query(l - 1);
  };

  for (int i = 1; i <= n; ++i) {
    std::vector<int> tmp(s[i].size());
    add(dfn[ node[i][ s[i].size() - 1 ] ], 1);
    for (int j = s[i].size() - 1; j >= 0; --j) {
      int ad = ed[ node[i][j] ] - Q(dfn[ node[i][j] ], dfn[ node[i][j] ] + siz[ node[i][j] ] - 1);
      (ans += vec[i][j] * ad % MOD) %= MOD;
      add(dfn[ node[i][j] ], ad), tmp[j] = ad;
    }
    add(dfn[ node[i][ s[i].size() - 1 ] ], -1);
    for (int j = s[i].size() - 1; j >= 0; --j) {
      add(dfn[ node[i][j] ], -tmp[j]);
    }
  }

  std::vector<int> fac(n + 1, 1);
  for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;

  std::cout << 2LL * ans % MOD * (n - 1) % MOD * fac[n - 2] % MOD << '\n';

  return 0;
}