#include <bits/stdc++.h>
#define MAXN ((int) 2e5)
using namespace std;
typedef pair<long long, int> pli;

int n, m, D[MAXN + 10];
vector<int> EX;

vector<int> e[MAXN + 10], v[MAXN + 10];
long long dis[MAXN + 10];

void dijkstra() {
    memset(dis, -1, sizeof(long long) * (n + 3));
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    for (int x : EX) pq.push(pli(0, x));
    while (!pq.empty()) {
        pli p = pq.top(); pq.pop();
        int sn = p.second;
        if (dis[sn] >= 0) continue;
        // 只有堵塞次数不够了，才能够更新 dis[sn]
        if (--D[sn] >= 0) continue;
        dis[sn] = p.first;
        for (int i = 0; i < e[sn].size(); i++) {
            int fn = e[sn][i];
            if (dis[fn] >= 0) continue;
            pq.push(pli(dis[sn] + v[sn][i], fn));
        }
    }
}

void solve() {
    int K; scanf("%d%d%d", &n, &m, &K);

    EX.clear();
    while (K--) {
        int x; scanf("%d", &x);
        EX.push_back(x);
    }

    for (int i = 1; i <= n; i++) scanf("%d", &D[i]);
    // 把终点的堵塞次数都改成 0，防止 dijkstra 无法开始
    for (int x : EX) D[x] = 0;

    for (int i = 1; i <= n; i++) e[i].clear(), v[i].clear();
    for (int i = 1; i <= m; i++) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        e[x].push_back(y); v[x].push_back(z);
        e[y].push_back(x); v[y].push_back(z);
    }

    dijkstra();
    printf("%lld\n", dis[1]);
}

int main() {
    int tcase=1;
    while (tcase--) solve();
    return 0;
}
