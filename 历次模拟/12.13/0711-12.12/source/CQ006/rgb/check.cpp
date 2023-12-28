#include <bits/stdc++.h>
#define int long long 
using namespace std;

inline int read() {
    int x = 0, f = 0; char ch = getchar();
    while(ch < '0' or ch > '9') f |= (ch == '-'), ch = getchar();
    while(ch >= '0' and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}
int __stk[128], __top;
inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    do { __stk[++__top] = x % 10, x /= 10; } while(x);
    while(__top) putchar(__stk[__top--] + '0');
}
bool stmer;
const int N = 260, M = N * N;
struct edge {
    int x, y, id;
} p[M];
int n, m;
int cnt[3], fa[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]);}
bool edmer;
signed main() {
    freopen("rgb.in", "r", stdin);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    for(int i = 0; i < 3; i++) cnt[i] = read(), n += cnt[i];
    m = read(), n++; char ch;
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), c = 0; cin >> ch;
        if(ch == 'g') c = 1; if(ch == 'b') c = 2;
        p[i] = {u, v, c};
    }
    freopen("rgb.out", "r", stdin);
    string s; cin >> s;
    if(s == "NO") puts("!!!"), exit(0);
    for(int i = 1; i <= m; i++) {
        cin >> ch;
        if(ch - '0') {
            int u = find(p[i].x), v = find(p[i].y);
            cnt[p[i].id]--;
            if(cnt[p[i].id] < 0) {
                write(p[i].id), putchar('\n');
                puts("WA"), exit(0);
            }
            if(u == v) {
                write(u), putchar(' '), write(v), putchar(' '), write(i), putchar('\n');
                puts("WA"), exit(0);
            } fa[u] = v;
        }
    }
    if(cnt[0] or cnt[1] or cnt[2]) {
        puts("rgb");
        puts("WA"), exit(0);
    } 
    puts("AC");
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}