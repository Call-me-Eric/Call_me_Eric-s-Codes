#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__);
#else
#define eprintf(...)
#endif

const int INF = 1e8;

struct segTree {
  vector<pair<int, int>> t;
  vector<int> u;
  int lst;

  void add(int v, int val) {
    u[v] += val;
    t[v].first += val;
  }

  void push(int v) {
    add(2 * v, u[v]);
    add(2 * v + 1, u[v]);
    u[v] = 0;
  }

  pair<int, int> get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) return {-INF, 0};
    if (L <= l && r <= R) return t[v];
    push(v);
    return max(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }
  
  void update(int v, int l, int r, int L, int R, int val) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
      add(v, val);
      return;
    }
    push(v);
    update(2 * v, l, (l + r) / 2, L, R, val);
    update(2 * v + 1, (l + r) / 2, r, L, R, val);
    t[v] = max(t[2 * v], t[2 * v + 1]);
  }

public:

  segTree(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    t.resize(2 * lst);
    u.resize(2 * lst);
    for (int i = 0; i < lst; i++) t[i + lst] = {0, i};
    for (int i = lst - 1; i > 0; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
  }

  void update(int l, int r, int val) {
    update(1, 0, lst, l, r, val);
  }

  pair<int, int> get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

};

const int MAXN = 1000005;
const int MAXL = 1000005;

char buf[MAXL + 1];

vector<int> hv[MAXL];


string solve(int n,int m) {
  int sum=0;
  for(int i=0;i<n;++i)
  {
  	int x,y;
  	scanf("%d",&x);sum+=x;
  	for(int j=0;j<x;++j)
  	{
  		scanf("%d",&y);
  		hv[y-1].push_back(i);
	  }
  		
  }
  cerr<<sum<<endl;
  vector<pair<int, int>> ones;
  {
    vector<int> last(n, -1);
    for (int i = 0; i < m; i++) {
      int f = ones.size();
      for(int j=0;j<(int)hv[i].size();++j)
      	ones.emplace_back(i+1,hv[i][j]);
      sort(ones.begin() + f, ones.end(),
           [&last](const pair<int, int> &a, const pair<int, int> &b) { return last[a.second] < last[b.second]; });
      for (int j = f; j < (int) ones.size(); j++) {
        int t = last[ones[j].second];
        last[ones[j].second] = j;
        ones[j].second = t;
      }
    }
  }
  n = ones.size();
  reverse(ones.begin(), ones.end());
  for (int i = 0; i < n; i++) {
    ones[i].second = n - ones[i].second - 1;
  }


  segTree tree(n);

  auto disable = [&tree, &ones, &n](int pos) {
    if (pos == n) return;
    tree.update(pos, pos + 1, -INF);
    tree.update(pos + 1, n, -1);
  };

  auto enable = [&tree, &ones, &n](int pos) {
    tree.update(pos, pos + 1, +INF);
    tree.update(pos + 1, n, +1);
  };

  for (int i = 0; i < n; i++) {
    tree.update(i, i + 1, ones[i].first + i);
    disable(ones[i].second);
  }

  string res(tree.get(0, n).first + 1, '0');

  int first = 0;
  while (first < n) {
    auto x = tree.get(first, n);
    if (x.first < 0) {
      break;
    }
    vector<int> to_revert;
    vector<int> to_revert2;

    int down = n;
    int last = -1;

    while (true) {
      auto y = tree.get(first, n);
      if (y.first > x.first) break;
      if (y.second < down || y.first < x.first) {
        to_revert2.insert(to_revert2.end(), to_revert.begin(), to_revert.end());
        to_revert.clear();
        if (y.first < x.first) {
          down = first - 1;
          break;
        }
        down = y.second;
      }
      if (ones[y.second].second < last) {
        break;
      }
      last = max(last, y.second);
      to_revert.push_back(y.second);
      tree.update(y.second, y.second + 1, -INF);
      enable(ones[y.second].second);
    }
    for (int pos : to_revert) {
      tree.update(pos, pos + 1, +INF);
      disable(ones[pos].second);
    }
    for (int pos : to_revert2) {
      tree.update(pos, pos + 1, +INF);
    }

    last = tree.get(first, n).second;

    int ptr = x.first;
    for (int i = first; i <= down; i++) {
      if (tree.get(i, i + 1).first > 0) {
        assert(ptr > 0);
        res[ptr--] = '1';
        tree.update(i + 1, n, -1);
      }
    }
    res[ptr--] = '0';
    for (int i = down + 1; i <= last; i++) {
      if (tree.get(i, i + 1).first > 0) {
        assert(ptr >= 0);
        res[ptr--] = '1';
        tree.update(i + 1, n, -1);
      }
    }

    first = last + 1;
  }
  reverse(res.begin(), res.end());
  return res;
}

int main() {
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
  int n,m;
  scanf("%d%d", &n,&m);
  
  string res = solve(n,m);

  for (int i = 0; i < (int)res.size(); i++) {
    if (i + 1 == (int)res.size() || res[i] == '1') {
      res = res.substr(i);
      break;
    }
  }
  int qwq=strlen(res.c_str());
  if(m<qwq)
  {
  	puts("-1");
  	return 0;
  }
  for(int i=1;i<=m-qwq;++i)
  	putchar('0');
  printf("%s\n", res.c_str());
}
