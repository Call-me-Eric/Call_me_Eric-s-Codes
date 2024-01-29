#include<bits/stdc++.h>
using namespace std;

inline int read() {
    int res = 0, f = 1; char ch;
    while((ch = getchar()) && (ch < '0' || ch > '9') && ch != '-');
    (ch == '-') ? f = -1 : res = ch - '0';
    while((ch = getchar()) && ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + ch - '0';
    return res * f;
}

inline void print(int x, char ch = '\n') {
    if(x < 0) putchar('-'), x = -x;
    static short prnum[21];
    short prcnt = 0;
    do { prnum[++prcnt] = x % 10; x /= 10; } while(x > 0);
    while(prcnt) putchar(prnum[prcnt--] + '0');
    putchar(ch);
}

const int MAXN = 255;

int R, G, B, n, m;
vector<pair<int, int> > e[MAXN][3];

struct Edge {
    int x, y, z;
}dat[MAXN * MAXN];

inline int getcol(char ch) {
    return (ch == 'r') ? 0 : ((ch == 'g') ? 1 : 2);
}

namespace Sol1 {
    int fa[MAXN];
    bool used[MAXN];
    vector<pair<pair<int, int>, int> > son[MAXN];
    inline int find(int x) { return (x == fa[x]) ? x : fa[x] = find(fa[x]); }
    int findrp(int x, int fa, int nd, int v) {
        if(x == nd) return v;
        for(auto it : son[x])
         if(it.first.first != fa) {
            int tmp = findrp(it.first.first, x, nd, it.first.second ? v : max(v, it.second));
            if(tmp != -1) return tmp;
         }
        return -1;
    }
}

void solve1() {
    using namespace Sol1;
    for(int i = 1; i <= n; i++) fa[i] = i;
    int cntr = 0, cntg = 0;
    for(int i = 1; i <= m; i++)
     if(dat[i].z == 0) {
        int x = dat[i].x, y = dat[i].y;
        if(find(x) == find(y)) continue;
        fa[find(x)] = find(y);
        son[x].push_back(make_pair(make_pair(y, 0), i));
        son[y].push_back(make_pair(make_pair(x, 0), i));
        used[i] = true; ++cntr;
     }
    for(int i = 1; i <= m; i++)
     if(dat[i].z == 1) {
        int x = dat[i].x, y = dat[i].y;
        if(find(x) != find(y)) {
            fa[find(x)] = find(y);
            son[x].push_back(make_pair(make_pair(y, 1), i));
            son[y].push_back(make_pair(make_pair(x, 1), i));
            used[i] = true; ++cntg;
        }
        else if(cntg < G) {
            int who = findrp(x, 0, y, -1);
            used[who] = false; --cntr;
            int xx = dat[who].x, yy = dat[who].y;
            auto it = son[xx].begin();
            while(it->first.first != yy) ++it;
            son[xx].erase(it);
            it = son[yy].begin();
            while(it->first.first != xx) ++it;
            son[yy].erase(it);
            son[x].push_back(make_pair(make_pair(y, 1), i));
            son[y].push_back(make_pair(make_pair(x, 1), i));
            used[i] = true; ++cntg;
        }
     }
    if(cntr != R || cntg != G) return puts("No"), void();
    puts("Yes");
    for(int i = 1; i <= m; i++) putchar(used[i] + '0');
    putchar('\n');
}

namespace Sol2 {
    int g[(1 << 5) + 5][6][6], h[(1 << 5) + 5][6][6];
    bool f[(1 << 5) + 5][6][6], used[125];
}

void solve2() {
    using namespace Sol2;
    for(int i = 0; i < n; i++) f[1 << i][0][0] = true, h[1 << i][0][0] = i + 1;
    for(int S = 0; S < (1 << n); S++)
     for(int i = 0; i <= n; i++)
      for(int j = 0; i + j <= n; j++)
       if(f[S][i][j])
        for(int x = 1; x <= n; x++)
         if(!((S >> (x - 1)) & 1)) {
            for(auto y : e[x][0])
             if((S >> (y.first - 1)) & 1) {
                f[S | (1 << (x - 1))][i + 1][j] = true;
                g[S | (1 << (x - 1))][i + 1][j] = y.second;
                h[S | (1 << (x - 1))][i + 1][j] = x;
             }
            for(auto y : e[x][1])
             if((S >> (y.first - 1)) & 1) {
                f[S | (1 << (x - 1))][i][j + 1] = true;
                g[S | (1 << (x - 1))][i][j + 1] = y.second;
                h[S | (1 << (x - 1))][i][j + 1] = x;
             }
            for(auto y : e[x][2])
             if((S >> (y.first - 1)) & 1) {
                f[S | (1 << (x - 1))][i][j] = true;
                g[S | (1 << (x - 1))][i][j] = y.second;
                h[S | (1 << (x - 1))][i][j] = x;
             }
         }
    if(!f[(1 << n) - 1][R][G]) return puts("No"), void();
    puts("Yes");
    int S = (1 << n) - 1, cntr = R, cntg = G;
    while(S) {
        int i = g[S][cntr][cntg], x = h[S][cntr][cntg];
        if(dat[i].z == 0) --cntr;
        else if(dat[i].z == 1) --cntg;
        S ^= (1 << (x - 1));
        used[i] = true;
    }
    for(int i = 1; i <= m; i++) putchar(used[i] + '0');
}

int main() {
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    R = read(); G = read(); B = read(); m = read(); n = R + G + B + 1;
    for(int i = 1, x, y, z; i <= m; i++) {
        x = read(); y = read();
        char ch;
        while((ch = getchar()) && (ch < 'a' || ch > 'z'));
        z = getcol(ch);
        dat[i] = {x, y, z};
        e[x][z].emplace_back(y, i);
        e[y][z].emplace_back(x, i);
    }
    if(B == 0) return solve1(), 0;
    if(n <= 5) return solve2(), 0;
    return 0;
}