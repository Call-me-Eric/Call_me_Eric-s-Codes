#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 200010;
int N, M, deg[MAXN];
int tot, head[MAXN];
struct Edge {
    int to, nxt;
} edge[MAXN << 1];
void add(int u, int v) {
    edge[++tot].to = v, edge[tot].nxt = head[u]; head[u] = tot;
}
int main() {
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    N = read(), M = read();
    for (int i = 1; i <= M; i++) {
        int u = read(), v = read();
        add(u, v), add(v, u);
        deg[u]++, deg[v]++;
    }
    bool flag = false; int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (deg[i] > 3) flag = true;
        if (deg[i] == 3) {
            cnt += deg[i];
            for (int e = head[i]; e; e = edge[e].nxt) {
                int v = edge[e].to;
                if (deg[v] >= 2) flag = true;
                deg[v] = 0;
            }
            deg[i] = 0;
        }
    }
    if (flag) return printf("-1\n"), 0;
    long long ans = 0;
    for (int i = 1; i <= N; i++)
        if (!deg[i]) ans++;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 1) {
            int tmp = 0;
            function<void(int,int)>dfs=[&](int u, int father) {
                tmp++, deg[u] = 0;
                for (int e = head[u]; e; e = edge[e].nxt) {
                    int v = edge[e].to;
                    if (v != father) dfs(v, u);
                }
            };
            dfs(i, 0);
            ans += 1ll * (tmp + 1)* tmp / 2;
        }    
    }
    for (int i = 1; i <= N; i++) 
        if (deg[i] == 2) cnt++;
    if (cnt) printf("1 %d\n", cnt);
    else printf("0 %lld\n", ans);
}
