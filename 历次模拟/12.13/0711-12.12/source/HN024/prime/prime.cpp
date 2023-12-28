#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;
using Huge = std::vector<int>;
void Hin(Huge &v) {
  std::string s;
  std::cin >> s, v.clear();
  bool occur = false;
  for (char c : s) {
    if (c != '0') occur = true;
    if (occur) v.emplace_back(c - '0');
  }
}
void AfterAdd(Huge &v) {
  for (int i = v.size() - 1; i; --i) {
    if (v[i] >= 10) v[i] -= 10, ++v[i - 1];
  }
  if (v[0] >= 10) {
    Huge nxt{1};
    v[0] -= 10;
    for (int e : v) nxt.emplace_back(e);
    v = std::move(nxt);
  }
}

const int kN = 1E5 + 5, kP = 998244353;
const std::vector<int> kTable = {
  649, 6049, 6649, 60049, 66049, 66649, 
  600049, 660049, 666049, 6000049, 6600049, 
  6660049
};
const std::vector<int> kEven = {0, 4, 6, 8};
void Add(int& x, int y) {
  if ((x += y) >= kP) x -= kP;
}
auto Sum(int x, int y) { return Add(x, y), x; }
std::array<int, kN> pow_4;

std::array<int, kN> suf, pre;
auto GetAns(Huge lim) { // ans for [1, lim).
  suf[lim.size()] = 0;
  for (int i = lim.size() - 1; ~i; --i) {
    suf[i] = 0;
    for (int t : kEven) {
      if (t < lim[i]) Add(suf[i], pow_4[lim.size() - i - 1]);
      if (t == lim[i]) Add(suf[i], suf[i + 1]);
    }
  }
  int ret = 0;

  {
    int compare = -1;
    // -1 : =
    // 0 : <
    // 1 : >
    for (int i = 0; i < lim.size(); ++i) {
      Add(ret, std::max(i64{0}, i64{i - 1}) * pow_4[lim.size() - 1 - i] % kP);
      if (i && (compare == 0 || (compare == -1 && lim[i] > 1))) {
        Add(ret, pow_4[lim.size() - 1 - i]);
      } else if (i && (compare == -1 && lim[i] == 1)) {
        Add(ret, suf[i + 1]);
      }

      if (i || (i == 0 && lim[0] > 1)) Add(ret, pow_4[lim.size() - 1 - i] % kP);
      if (!i && lim[0] == 1) Add(ret, suf[i + 1]);

      int cur = ((i == 0) ? 8 : 0);
      if (compare == -1 && cur > lim[i]) compare = 1;
      if (compare == -1 && cur < lim[i]) compare = 0;
    }
  }

  {
    std::vector<int> match{91, 901, 981, 9081, 9801};
    for (int i = 0; i < lim.size(); ++i) {
      int lt = 0, eq = 0;
      if (i + 1 <= 4) {
        int v = 0;
        for (int j = 0; j <= i; ++j) v = v * 10 + lim[j];
        auto it = std::lower_bound(ALL(match), v);
        lt = it - begin(match), eq = (it != end(match) && *it == v);
      } else {
        lt = match.size();
      }
      Add(ret, i64{lt} * pow_4[lim.size() - 1 - i] % kP);
      Add(ret, i64{eq} * suf[i + 1] % kP);
    }
  }

  Add(ret, suf[0]);

  {
    std::vector<int> match{949, 9469, 94669};
    for (int i = 0; i < lim.size(); ++i) {
      int lt = 0, eq = 0;
      if (i + 1 <= 5) {
        int v = 0;
        for (int j = 0; j <= i; ++j) v = v * 10 + lim[j];
        auto it = std::lower_bound(ALL(match), v);
        lt = it - begin(match), eq = (it != end(match) && *it == v);
      } else {
        lt = match.size();
      }
      Add(ret, i64{lt} * pow_4[lim.size() - 1 - i] % kP);
      Add(ret, i64{eq} * suf[i + 1] % kP);
    }
  }

  {
    std::vector<int> match = kTable;
    for (int i = 0; i < lim.size(); ++i) {
      int lt = 0, eq = 0;
      if (i + 1 <= 7) {
        int v = 0;
        for (int j = 0; j <= i; ++j) v = v * 10 + lim[j];
        auto it = std::lower_bound(ALL(match), v);
        lt = it - begin(match), eq = (it != end(match) && *it == v);
      } else {
        lt = match.size();
      }
      Add(ret, i64{lt} * pow_4[lim.size() - 1 - i] % kP);
      Add(ret, i64{eq} * suf[i + 1] % kP);
    }
  }

  {
    // -1 : me < u
    // 0 : me = u
    // 1 : me > u
    int compare = ((4 < lim[0]) ? -1 : (4 == lim[0] ? 0 : 1));
    for (int i = 1; i < lim.size(); ++i) {
      Add(ret, i64{i - 1} * pow_4[lim.size() - i - 1] % kP);
      if (compare == -1) Add(ret, pow_4[lim.size() - i - 1]);
      if (compare == 0 && lim[i] == 9) Add(ret, suf[i + 1]);
      if (compare == 0 && 6 < lim[i]) compare = -1;
      if (compare == 0 && 6 > lim[i]) compare = 1;
    }
  }

  {
    bool ok = true;
    for (int i = 0; i < lim.size(); ++i) {
      pre[i] = i64{i ? pre[i - 1] : 0} * 3 % kP;
      if (ok) Add(pre[i], (lim[i] > 0)), Add(pre[i], (lim[i] > 6));
      ok &= (lim[i] == 0 || lim[i] == 6 || lim[i] == 9);
    }
    ok = true;
    for (int i = 0; i + 1 < lim.size(); ++i) {
      Add(ret, i64{pre[i]} * pow_4[lim.size() - 2 - i] % kP);
      ok &= (lim[i] == 0 || lim[i] == 6 || lim[i] == 9);
      if (lim[i + 1] == 9 && ok) Add(ret, suf[i + 2]);
    }
  }
  return ret;
}

void Pre() {
  pow_4[0] = 1;
  for (int i = 1; i < kN; ++i) pow_4[i] = i64{pow_4[i - 1]} * 4 % kP;
}
void Solve() {
  Huge l, r;
  Hin(l), Hin(r);
  ++r.back(), AfterAdd(r);
  std::cout << Sum(GetAns(r), kP - GetAns(l)) << '\n';
}

auto main() -> int {
  freopen("prime.in", "r", stdin);
  freopen("prime.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int t;
  for (Pre(), std::cin >> t; t; --t) Solve();
  return 0;
}