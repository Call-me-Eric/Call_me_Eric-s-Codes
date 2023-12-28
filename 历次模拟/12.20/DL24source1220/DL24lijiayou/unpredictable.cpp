# include <bits/stdc++.h>
# include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

namespace kh {
  ifstream cin("unpredictable.in");
  ofstream cout("unpredictable.out");
  constexpr int P[]{ 0x2a980003, 0x2e6e0c6b };
  constexpr int B[]{ 0x03d09d98, 0x23d86b45 };
  default_random_engine rng((random_device())());
  uniform_int_distribution<int> rand[2];
  constexpr int Q(998'244'353);
  constexpr int N(1'000'000);
  constexpr int S(1'000'000);
  template <typename T, int N>
    class mempool {
      T mem[N], *p = mem;
      public:
      T* alloc(int const n)
      { return (p += n) - n; }
    };
  int n;
  char* s[N + 1];
  int * w[N + 1];
  int * p[N + 1];
  int * q[N + 1];
  int val[2][26];
  int pow[2][N + 1];
  gp_hash_table<long, pair<int, int>> mem;
  int ans;
  void main() {
    pow[1][0] = pow[0][0] = 1;
    for (int i(1); i <= S; ++i) {
      pow[0][i] = 1l * pow[0][i - 1] * B[0] % P[0];
      pow[1][i] = 1l * pow[1][i - 1] * B[1] % P[1];
    }
    rand[0] = uniform_int_distribution<int>(0, P[0] - 1);
    rand[1] = uniform_int_distribution<int>(1, P[1] - 1);
    for (int i(0); i != 26; ++i) {
      val[0][i] = rand[0](rng);
      val[1][i] = rand[1](rng);
    }
    cin >> n;
    for (int i(1); i <= n; ++i) {
      static mempool<char, 2 * N + S> mems;
      static mempool<int , 2 * N + S> memw;
      static mempool<int , 2 * N + S> memp;
      static mempool<int , 2 * N + S> memq;
      static char t[S + 1];
      cin >> t;
      int const len(strlen(t));
      s[i] = mems.alloc(len + 2);
      w[i] = memw.alloc(len + 2);
      p[i] = memp.alloc(len + 2);
      q[i] = memq.alloc(len + 2);
      strcpy(s[i] + 1, t);
      for (int j(1); j <= len; ++j) cin >> w[i][j];
      for (int j(2); j <= len; ++j) {
        p[i][j] = p[i][j - 1];
        while (p[i][j] && s[i][p[i][j] + 1] != s[i][j])
          p[i][j] = p[i][p[i][j]];
        p[i][j] += s[i][p[i][j] + 1] == s[i][j];
      }
      reverse(s[i] + 1, s[i] + len + 1);
      for (int j(2); j <= len; ++j) {
        q[i][j] = q[i][j - 1];
        while (q[i][j] && s[i][q[i][j] + 1] != s[i][j])
          q[i][j] = q[i][q[i][j]];
        q[i][j] += s[i][q[i][j] + 1] == s[i][j];
      }
      reverse(s[i] + 1, s[i] + len + 1);
      for (int j(len), k[2]{}, l(1); j >= 1; --j, ++l) {
        k[0] = (1l * k[0] * B[0] + val[0][s[i][j] - 'a']) % P[0];
        k[1] = (1l * k[1] * B[1] + val[1][s[i][j] - 'a']) % P[1];
        auto& mem(kh::mem[k[0] + 1l * k[1] * P[0]]);
        ++mem.first, mem.second = (mem.second + w[i][l] - w[i][q[i][l]]) % Q;
      }
    }
    for (int i(1); i <= n; ++i) {
      for (int j(1), k[2]{}; s[i][j]; ++j) {
        k[0] = (k[0] + 1l * val[0][s[i][j] - 'a'] * pow[0][j - 1]) % P[0];
        k[1] = (k[1] + 1l * val[1][s[i][j] - 'a'] * pow[1][j - 1]) % P[1];
        auto const& mem(kh::mem[k[0] + 1l * k[1] * P[0]]);
        ans = (ans + 1l * (w[i][j] - w[i][p[i][j]]) * mem.first) % Q;
        ans = (ans + mem.second) % Q;
      }
      ans = (ans - 2l * w[i][strlen(s[i] + 1)]) % Q;
    }
    ans = 1l * ans * (n - 1) % Q;
    for (int i(1); i <= n - 2; ++i)
      ans = 1l * ans * i % Q;
    cout << (ans + Q) % Q << endl;
  }
}

int main() { kh::main(); }
