# include <cstdio>
# include <vector>
# include <bitset>
# include <cctype>
# include <iostream>
# include <algorithm>
# include <functional>

class IO {
	static constexpr int MAXS = 1 << 22;
	
	char buf[MAXS], *p1 = buf, *p2 = buf;
	
	# define GetC() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXS, stdin), p1 == p2) ? EOF : *p1 ++)
	
 public:
	template <typename T> void read(T& x) {
		x = 0; char ch = GetC();
		for (; !isdigit(ch); ch = GetC());
		for (; isdigit(ch); ch = GetC()) x = x * 10 + ch - '0';
	}
	
	template <typename T, typename ...Args> void read(T& x, Args& ...rest) {
		read(x), read(rest...);
	}
} io;

int cntN;

int main() {

  freopen("compose.in", "r", stdin);
  freopen("compose.out", "w", stdout);

  int n, k, q;
  io.read(n, k, q);

  std::vector<std::vector<int> > a(k + 1), b(k + 1);

  for (int i = 1; i <= k; ++i) {
    a[i].resize(n + 1);
    for (int j = 1; j <= n; ++j) {
      io.read(a[i][j]);
    }
  }

  std::vector<int> op(q + 1), x(q + 1), y(q + 1);

  cntN = k;
  
  std::vector<int> vec;

  std::vector<bool> vis(n + 1);
  std::vector<int> trans(n + 1);

  for (int i = 1; i <= q; ++i) {
    io.read(op[i], x[i], y[i]);
    if (op[i] != 3) ++cntN;
    else vec.push_back(y[i]), vis[ y[i] ] = true;
  }

  std::sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());

  for (int i = 1; i <= q; ++i) {
    if (op[i] == 3)
      trans[ y[i] ] = std::lower_bound(vec.begin(), vec.end(), y[i]) - vec.begin();
  }

  for (int i = 1; i <= k; ++i) {
    b[i].resize(vec.size());
    for (int j = 1; j <= n; ++j) {
      if (vis[j]) b[i][ trans[j] ] = a[i][j];
    }
  }

  auto solve1 = [&]() {
    std::vector<std::bitset<30000> > bit(cntN + 1);

    std::vector<int> ans(q + 1);

    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= k; ++j) {
        bit[j].reset();
        for (int p = 0; p < b[j].size(); ++p)
          if (b[i][p] <= b[j][p]) bit[j].set(p);
      }
      int cnt = k;
      for (int j = 1; j <= q; ++j) if (op[j] != 3) {
        if (op[j] == 1) 
          bit[++cnt] = bit[ x[j] ] | bit[ y[j] ];
        else bit[++cnt] = bit[ x[j] ] & bit[ y[j] ];
      }
      for (int j = 1; j <= q; ++j) if (op[j] == 3) {
        if (bit[ x[j] ][ trans[ y[j] ] ]) 
          ans[j] = std::max(ans[j], b[i][ trans[ y[j] ] ]);
      }
    }

    for (int i = 1; i <= q; ++i) {
      if (op[i] == 3) printf("%d\n", ans[i]);
    }
  };

  auto solve2 = [&]() {
    std::vector<std::bitset<40000> > bit(cntN + 1);

    std::vector<int> ans(q + 1);

    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= k; ++j) {
        bit[j].reset();
        for (int p = 0; p < b[j].size(); ++p)
          if (b[i][p] <= b[j][p]) bit[j].set(p);
      }
      int cnt = k;
      for (int j = 1; j <= q; ++j) if (op[j] != 3) {
        if (op[j] == 1) 
          bit[++cnt] = bit[ x[j] ] | bit[ y[j] ];
        else bit[++cnt] = bit[ x[j] ] & bit[ y[j] ];
      }
      for (int j = 1; j <= q; ++j) if (op[j] == 3) {
        if (bit[ x[j] ][ trans[ y[j] ] ]) 
          ans[j] = std::max(ans[j], b[i][ trans[ y[j] ] ]);
      }
    }

    for (int i = 1; i <= q; ++i) {
      if (op[i] == 3) printf("%d\n", ans[i]);
    }
  };

  auto solve3 = [&]() {
    std::vector<std::bitset<100000> > bit(cntN + 1);

    std::vector<int> ans(q + 1);

    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= k; ++j) {
        bit[j].reset();
        for (int p = 0; p < b[j].size(); ++p)
          if (b[i][p] <= b[j][p]) bit[j].set(p);
      }
      int cnt = k;
      for (int j = 1; j <= q; ++j) if (op[j] != 3) {
        if (op[j] == 1) 
          bit[++cnt] = bit[ x[j] ] | bit[ y[j] ];
        else bit[++cnt] = bit[ x[j] ] & bit[ y[j] ];
      }
      for (int j = 1; j <= q; ++j) if (op[j] == 3) {
        if (bit[ x[j] ][ trans[ y[j] ] ]) 
          ans[j] = std::max(ans[j], b[i][ trans[ y[j] ] ]);
      }
    }

    for (int i = 1; i <= q; ++i) {
      if (op[i] == 3) printf("%d\n", ans[i]);
    }
  };

  auto solve4 = [&]() {
    std::vector<std::bitset<20000> > bit(cntN + 1);

    std::vector<int> ans(q + 1);

    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= k; ++j) {
        bit[j].reset();
        for (int p = 0; p < b[j].size(); ++p)
          if (b[i][p] <= b[j][p]) bit[j].set(p);
      }
      int cnt = k;
      for (int j = 1; j <= q; ++j) if (op[j] != 3) {
        if (op[j] == 1) 
          bit[++cnt] = bit[ x[j] ] | bit[ y[j] ];
        else bit[++cnt] = bit[ x[j] ] & bit[ y[j] ];
      }
      for (int j = 1; j <= q; ++j) if (op[j] == 3) {
        if (bit[ x[j] ][ trans[ y[j] ] ]) 
          ans[j] = std::max(ans[j], b[i][ trans[ y[j] ] ]);
      }
    }

    for (int i = 1; i <= q; ++i) {
      if (op[i] == 3) printf("%d\n", ans[i]);
    }
  };

  auto solve5 = [&]() {
    std::vector<std::bitset<53000> > bit(cntN + 1);

    std::vector<int> ans(q + 1);

    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= k; ++j) {
        bit[j].reset();
        for (int p = 0; p < b[j].size(); ++p)
          if (b[i][p] <= b[j][p]) bit[j].set(p);
      }
      int cnt = k;
      for (int j = 1; j <= q; ++j) if (op[j] != 3) {
        if (op[j] == 1) 
          bit[++cnt] = bit[ x[j] ] | bit[ y[j] ];
        else bit[++cnt] = bit[ x[j] ] & bit[ y[j] ];
      }
      for (int j = 1; j <= q; ++j) if (op[j] == 3) {
        if (bit[ x[j] ][ trans[ y[j] ] ]) 
          ans[j] = std::max(ans[j], b[i][ trans[ y[j] ] ]);
      }
    }

    for (int i = 1; i <= q; ++i) {
      if (op[i] == 3) printf("%d\n", ans[i]);
    }
  };

  if (vec.size() <= 20000) solve4();
  if (vec.size() <= 30000) solve1();
  else if (vec.size() <= 40000) solve2();
  else if (vec.size() <= 53000) solve5();
  else solve3();

  return 0;
}