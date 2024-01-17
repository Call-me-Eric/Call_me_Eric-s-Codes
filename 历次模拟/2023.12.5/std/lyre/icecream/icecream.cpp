# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  using pair = std::pair<int, int>;
  inline namespace io {
    class scanner {
      FILE* const stream; char buffer[BUFSIZ];
      char *head = buffer, *tail = buffer;
      void flush() {
        assert(head == tail), head = tail = buffer;
        tail += fread(buffer, sizeof(char), BUFSIZ, stream);
      }
    public:
      scanner(FILE* const stream = stdin) : stream(stream) {}
      scanner(const char* const filename) : stream(fopen(filename, "r")) {}
      ~scanner() { fclose(stream); }
      char getc() {
        if (head == tail) flush();
        return head == tail ? EOF : *head++;
      }
      template <typename T>
        T get() {
          char ch;
          while (!isgraph(ch = getc()) && ch != EOF);
          assert(isdigit(ch)); T res(0);
          while (isdigit(ch)) res = res * 10 + (ch - '0'), ch = getc();
          return res;
        }
      template <typename T>
        void read(T &value) { value = get<T>(); }
      template <typename T, typename ...U>
        void read(T &value, U &...args)
        { read(value), read(args...); }
    };
    class printer {
      FILE* const stream;
      char buffer[BUFSIZ], *ptr = buffer;
      void flush() {
        fwrite(buffer, sizeof(char), ptr - buffer, stream);
        ptr = buffer;
      }
    public:
      printer(FILE* const stream = stdout) : stream(stream) {}
      printer(const char* const filename) : stream(fopen(filename, "w")) {}
      ~printer() { flush(), fclose(stream); }
      void putc(char const ch) {
        if (ptr - buffer == BUFSIZ) flush();
        *ptr++ = ch;
      }
      template <typename T>
        void write(T value) {
          static char stk[CHAR_BIT * sizeof(T)], *top(stk);
          while (*top++ = value % 10 + '0', value /= 10);
          while (putc(*--top), top != stk);
        }
      template <typename T>
        void writeln(T const value) { write(value), putc('\n'); }
    };
  }
  constexpr size_t N(1'000'100);
  constexpr size_t M(8'100);
  int n, q, B;
  struct hash_func {
    constexpr size_t operator()(pair const &v) const
    { return v.first * N + v.second; }
  };
  unordered_map<pair, int, hash_func> w;
  unordered_map<int, int> id;
  struct query {
    int opt, x, y, ans;
  } u[N];
  struct value {
    int size;
    vector<int> occ;
  } v[N];
  set<int> s[N];
  bitset<M> t[N];
  inline void ins(int x, int y) {
    for (auto const z : v[y].occ) {
      assert(x != z);
      if (w.count(minmax(x, z)))
        ++w[minmax(x, z)];
    }
    v[y].occ.push_back(x);
    s[x].insert(y);
  }
  inline int solve(int x, int y) {
    if (x == y) return s[x].size();
    return s[x].size() + s[y].size() - w[minmax(x, y)];
  }
  void main() {
    scanner scanner("icecream.in");
    printer printer("icecream.out");
    scanner.read(n, q);
    for (int i(0); i < q; ++i) {
      auto &[opt, x, y, z](u[i]);
      scanner.read(opt, x, y);
      if (opt == 1) {
        ++v[y].size;
        assert(!s[x].count(y));
      } else if (x != y) {
        w[minmax(x, y)] = 0;
      }
    }
    B = sqrt(n / 64 + 1);
    for (int i(0); i < q; ++i) {
      auto &[opt, x, y, z](u[i]);
      if (opt == 1 && v[y].size <= B)
        ins(x, y);
      else if (opt == 2)
        z = solve(x, y);
    }
    for (int i(1), j(0); i <= n; ++i) {
      if (v[i].size > B)
        id[i] = ++j;
    }
    for (int i(0); i < q; ++i) {
      auto &[opt, x, y, z](u[i]);
      if (opt == 1 && v[y].size > B)
        t[x].set(id[y]);
      else if (opt == 2)
        z += (t[x] | t[y]).count();
    }
    for (int i(0); i < q; ++i) {
      if (u[i].opt == 2)
        printer.writeln(u[i].ans);
    }
  }
}

int main() { lyre::main(); }
