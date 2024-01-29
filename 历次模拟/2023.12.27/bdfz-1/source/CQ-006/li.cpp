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
const int N = 2e5 + 10;
int n, m, ans, cnt, sum, tot;
int d[N];
vector<int> e[N];
bool vis[N];
void dfs(int x) {
    vis[x] = 1, tot++, d[e[x].size()]++;
    for(auto v : e[x]) if(!vis[v]) dfs(v);
}
bool edmer;
signed main() {
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        e[u].push_back(v), e[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) if(!vis[i]) {
        d[0] = d[1] = d[2] = d[3] = tot = 0;
        dfs(i);
        if(d[2] == tot) {
            if(!ans) ans = 1, sum = 0;
            sum += tot;
        }
        else if(d[3] == 1 and tot == 4 and d[1] == 3) {
            if(!ans) ans = 1, sum = 0;
            sum += tot - 1;
        }
        else if(d[1] == 2 and d[2] == tot - 2) sum += ans ? 0 : (tot * (tot + 1) / 2);
        else if(d[0] ^ tot) puts("-1"), exit(0); else sum += ans ^ 1;
    } write(ans), putchar(' '), write(sum);
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}