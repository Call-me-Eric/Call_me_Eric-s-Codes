# include <bits/stdc++.h>

using namespace std;

namespace io {
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

int main() {
  io::scanner scanner("icecream.in");
  io::printer printer("icecream.out");
  int a, b;
  scanner.read(a, b);
  printer.writeln(a + b);
}