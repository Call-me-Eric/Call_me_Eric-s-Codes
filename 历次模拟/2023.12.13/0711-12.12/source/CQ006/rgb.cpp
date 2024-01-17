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
int n, m, tot;
int cnt[3], pos[3], fa[N], fr[N];
int vis[N], vise[M], flag[M];
vector<edge> E[3], e[N];
namespace sub1 {
    void dfs(int x, int f) {
        fa[x] = f, vis[x] = tot;
        for(auto l : e[x]) if(l.x ^ f)
            fr[l.x] = l.id, dfs(l.x, x);
    }
    void del(int x) {
        flag[x] = 0;
        cnt[p[x].id]++; int u = p[x].x, v = p[x].y;
        if((++vise[x]) < 2) E[p[x].id].push_back({u, v, x});
        for(int i = 0; i < e[u].size(); i++)
            if(e[u][i].x == v) {
                swap(e[u][i], e[u].back());
                e[u].pop_back(); break;
            }
        for(int i = 0; i < e[v].size(); i++)
            if(e[v][i].x == u) {
                swap(e[v][i], e[v].back());
                e[v].pop_back(); break;
            }
    }
    void add(int x) {
        flag[x] = 1;
        int u = p[x].x, v = p[x].y, id = p[x].id; cnt[id]--;
        e[u].push_back({v, id, x}), e[v].push_back({u, id, x});
    }
    void solve() {
        while(cnt[0] or cnt[1] or cnt[2]) {
            for(int i = 0; i < 3; i++) if(cnt[i] > 0) {
                for(int j = pos[i]; j < E[i].size() and cnt[i] > 0; j = (++pos[i])) {
                    int u = E[i][j].x, v = E[i][j].y, id = E[i][j].id;
                    tot++, dfs(u, 0);
                    if(vis[v] ^ tot) { add(id); continue; }
                    int x = 0, y = 1;
                    if(i == 0) x = 2; if(i == 1) y = 2;
                    if(cnt[x] - E[x].size() > cnt[y] - E[y].size()) swap(x, y);
                    int g = 0, now = v;
                    while(fa[now]) {
                        int l = fr[now]; now = fa[now];
                        if(!g and p[l].id != i) g = l;
                        else if(p[g].id == y and p[l].id == x) g = l;
                        else if(p[g].id == y and vise[l] < vise[g]) g = l;
                        else if(p[g].id == x and p[l].id == x and vise[l] < vise[g]) g = l;
                    }
                    if(!g and (++vise[id]) < 2) E[i].push_back({u, v, id});
                    else if(g) del(g), add(id);
                } if(cnt[i] > 0) puts("NO"), exit(0);
            }
        } 
        if(cnt[0] or cnt[1] or cnt[2]) puts("NO");
        else {
            puts("YES");
            for(int i = 1; i <= m; i++) putchar(flag[i] + '0');
        }
    }
}
bool edmer;
signed main() {
    freopen("rgb.in", "r", stdin);
    freopen("rgb.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    for(int i = 0; i < 3; i++) cnt[i] = read(), n += cnt[i];
    m = read(), n++; char ch;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), c = 0; cin >> ch;
        if(ch == 'g') c = 1; if(ch == 'b') c = 2;
        E[c].push_back({u, v, i}), p[i] = {u, v, c};
    } sub1 :: solve();

    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}