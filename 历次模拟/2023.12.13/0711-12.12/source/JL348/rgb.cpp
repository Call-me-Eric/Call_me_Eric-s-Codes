#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 260;
int N, M, r, g, b;
int fa[MAXN];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
struct Edge {
    int u, v; char c;
} edge[MAXN * MAXN];
void check(int s) {
    for (int i = 1; i <= N; i++) fa[i] = i;
    int cntr = 0, cntg = 0, cntb = 0;
    for (int i = 0; i < M; i++) if ((s >> i) & 1){
        int u = edge[i].u, v = edge[i].v; char c = edge[i].c;
        cntr += (c == 'r'), cntg += (c == 'g'), cntb += (c == 'b');
        u = find(u), v = find(v);
        if (u == v) return ;
        fa[u] = v;
    }
    if (cntr == r and cntg == g and cntb == b) {
        printf("YES\n");
        for (int i = 0; i < M; i++) 
            printf("%d", (s >> i) & 1);
        exit(0);
    }
}
int main() {
    freopen("rgb.in", "r", stdin);
    freopen("rgb.out", "w", stdout);
    r = read(), g = read(), b = read(), M = read();
    N = r + g + b + 1;
    if (N > 5) return printf("NO\n"), 0;
    for (int i = 0; i < M; i++) {
        int u = read(), v = read(); char ch = getchar();
        while (ch != 'r' and ch != 'g' and ch != 'b') ch = getchar();
        edge[i] = (Edge){ u, v, ch };
    }
    for (int i = 0; i < (1 << M); i++) {
        if (__builtin_popcount(i) != N - 1) continue;
        check(i);
    }
    printf("NO\n");
}
