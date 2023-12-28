#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch  < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxm = 3e3 + 10,maxn = 1e6 + 10;
int n ,q;
struct qry{
    int opt, x, y;
    qry(int o = 0,int x = 0,int y = 0):opt(o),x(x),y(y){}
}tmp[maxn];

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
};
int res[maxn];
namespace subtask1{
bitset<maxm> bt[maxm];
void solve(){
    int opt, x, y;
    for(int i = 1;i <= q;i++){
        opt = tmp[i].opt; x = tmp[i].x;y = tmp[i].y;
        if(opt == 1)bt[x].set(y);
        else{
            int ans = 0;
            if(bt[x].count() == 0 || bt[y].count() == 0){ans = bt[x].count() + bt[y].count();}
            else ans = (bt[x] | bt[y]).count();
            res[i] = ans;
        }
    }
    return;
}
};
namespace subtask2{
    int summ[maxn << 3],L[maxn << 3],R[maxn << 3];
    int tot,head[maxn], len;
    bitset<510> st[maxn * 2];int cnt;
    unordered_map<int,int> id;
    void insert(int l,int r,int pos,int p){
        if(l == r){summ[p] = 1;return;}
        if(r - l + 1 <= 500){
            if(!id[p])id[p] = ++cnt;
            st[id[p]].set(pos - l);
            summ[p]++;
            return;
        }
        int mid = l + r >> 1;
        if(pos <= mid){
            if(!L[p])L[p] = ++tot;
            insert(l,mid,pos,L[p]);
        }
        else{
            if(!R[p])R[p] = ++tot;
            insert(mid + 1, r,pos,R[p]);
        }
        summ[p] = summ[L[p]] + summ[R[p]];
    }
    int query(int l,int r,int p1,int p2){
        if(l == r){return !(summ[p1] + summ[p2]);}
        if(!summ[p1] || !summ[p2])return r - l + 1 - summ[p1] - summ[p2];
        if(r - l + 1 <= 500){return r - l + 1 - (st[id[p1]] | st[id[p2]]).count();}
        int mid = l + r >> 1;
        return query(l,mid,L[p1],L[p2]) + query(mid + 1,r,R[p1],R[p2]);
    }
    unordered_map<int,int> mp;
    void solve(){
        for(int i = 1;i <= n;i++)head[i] = ++tot;
        for(int i = 1;i <= q;i++)if(tmp[i].opt == 1 && !mp[tmp[i].y])mp[tmp[i].y] = ++len;
        int opt, x, y;
        for(int i = 1;i <= q;i++){
            // cerr << "y = " << tmp[i].y << " mp = " << mp[tmp[i].y] << endl;
            opt = tmp[i].opt;x = tmp[i].x;y = tmp[i].y;
            if(opt == 1){y = mp[y];insert(1,len,y,head[x]);}
            else{res[i] = len - query(1,len,head[y],head[x]);}
            // cerr << "res = " << res[i] << endl;
        }
        // cerr << "len = " << len;
    }
};
int siz[maxn];
signed main(){
    io::scanner scanner("icecream.in");
    io::printer printer("icecream.out");
    scanner.read(n,q);
    int opt, x, y;
    for(int i = 1;i <= q;i++){
        scanner.read(opt,x,y);
        tmp[i] = qry(opt,x,y);
    }
    if(n <= 3e3){subtask1::solve();}
    else{subtask2::solve();}
    for(int i = 1;i <= q;i++){
        if(tmp[i].opt == 2){printer.writeln(res[i]);}
    }
    return 0;
}
/*
3 5
1 1 2
1 2 3
1 3 2
2 1 2
2 1 3
*/