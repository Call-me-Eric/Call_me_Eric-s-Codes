# include <cstdio>
# include <vector>
# include <set>
# include <iterator>
# include <algorithm>
# include <functional>

# define int long long

signed main() {

  freopen("value.in", "r", stdin);
  freopen("value.out", "w", stdout);

  int n;
  scanf("%lld", &n);

  struct Str { int a, b, d; }; std::vector<Str> vec(n + 1);

  std::vector<int> d;

  for (int i = 1; i <= n; ++i) 
    scanf("%lld %lld", &vec[i].a, &vec[i].b), d.push_back(vec[i].b);

  std::sort(d.begin(), d.end());
  d.erase(unique(d.begin(), d.end()), d.end());

  std::vector<int> val(n + 1);

  for (int i = 1; i <= n; ++i) {
    vec[i].d = std::lower_bound(d.begin(), d.end(), vec[i].b) - d.begin() + 1;
    val[ vec[i].d ] = vec[i].b;
  }

  std::sort(vec.begin() + 1, vec.end(), [&](const Str& A, const Str& B) {
    return A.a > B.a;
  });

  int N = n + 1 << 1;

  std::vector<int> tr(N + 1);

  auto add = [&](int x) {
    for (; x <= N; x += x & -x)
      tr[x] ++;
  };

  auto query = [&](int x) {
    int res = 0;
    for (; x; x -= x & -x)
      res += tr[x]; return res;
  };

  int ans = n * vec[n].a, mx = 0;

  std::set<int> st;
  for (int i = n; i >= 1; --i) {
    int sum = (i - 1) * vec[i - 1].a;

    add(vec[i].d);
    if (!mx) mx = vec[i].d;

    int tmp = mx;

    int S = query(N);

    auto x = st.insert(vec[i].d).first;
    if (*x <= vec[i - 1].a && sum + (S - query(*x - 1)) * val[*x] > ans)
      ans = sum + (S - query(*x - 1)) * val[*x], mx = *x;

    for (int cnt = 0; x != st.begin() && cnt <= 75; cnt ++) {
      x = std::prev(x);
      if (*x <= vec[i - 1].a && sum + (S - query(*x - 1)) * val[*x] > ans)
        ans = sum + (S - query(*x - 1)) * val[*x], mx = *x;
    }

    x = st.find(tmp);
    if (*x <= vec[i - 1].a && sum + (S - query(*x - 1)) * val[*x] > ans)
      ans = sum + (S - query(*x - 1)) * val[*x], mx = *x;
      
    for (int cnt = 0; x != st.begin() && cnt <= 75; cnt ++) {
      x = std::prev(x);
      if (*x <= vec[i - 1].a && sum + (S - query(*x - 1)) * val[*x] > ans)
        ans = sum + (S - query(*x - 1)) * val[*x], mx = *x;
    }

    x = st.find(tmp);
    for (int cnt = 0; std::next(x) != st.end() && cnt <= 75; cnt ++) {
      x = std::next(x);
      if (*x <= vec[i - 1].a && sum + (S - query(*x - 1)) * val[*x] > ans)
        ans = sum + (S - query(*x - 1)) * val[*x], mx = *x;
    }
  }

  printf("%lld\n", ans);

  return 0;
}