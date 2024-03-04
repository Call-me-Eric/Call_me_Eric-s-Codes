#include <bits/stdc++.h>
using namespace std;
int k, X[2001], a[8001], n, head[8001], to[32000001], nex[32000001], w[32000001], cnt = 1, s, t, dep[8001],
                                                                                  cur[8001];
bool tag[10000002];
inline void add(int x, int y, int z) { to[++cnt] = y, nex[cnt] = head[x], w[cnt] = z, head[x] = cnt; }
inline bool bfs() {
    for (int i = 1; i <= t; ++i) dep[i] = 0, cur[i] = head[i];
    queue<int> q;
    q.push(s);
    dep[s] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = nex[i]) {
            int y = to[i];
            if (w[i] && !dep[y]) {
                dep[y] = dep[x] + 1;
                q.push(y);
            }
        }
    }
    return dep[t];
}
inline int dinic(int x, int in) {
    if (x == t)
        return in;
    int out = 0;
    for (int &i = cur[x]; i; i = nex[i]) {
        int y = to[i];
        if (w[i] && dep[y] == dep[x] + 1) {
            int jjxsm = dinic(y, min(in - out, w[i]));
            if (jjxsm) {
                out += jjxsm;
                w[i] -= jjxsm;
                w[i ^ 1] += jjxsm;
                if (in == out)
                    break;
            }
        }
    }
    if (in != out)
        dep[x] = 0;
    return out;
}
inline bool check(int x) {
    if (x == 1)
        return 0;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return 0;
    return 1;
}
int main() {
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) scanf("%d", &X[i]);
    for (int i = 1; i <= k; ++i) tag[X[i]] ^= 1, tag[X[i] + 1] ^= 1;
    for (int i = 1; i <= 10000001; ++i)
        if (tag[i])
            a[++n] = i;
    for (int i = 2; i <= n; ++i) {
        if (a[i] == a[i - 1]) {
            cout << 114514;
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if ((a[j] - a[i]) & 1) {
                if (check(a[j] - a[i])) {
                    if (a[i] & 1) {
                        add(i, j, 1);
                        add(j, i, 0);
                    } else {
                        add(j, i, 1);
                        add(i, j, 0);
                    }
                }
            }
        }
    }
    s = n + 1, t = s + 1;
    int N1 = 0, N0 = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] & 1) {
            add(s, i, 1);
            add(i, s, 0);
            ++N1;
        } else {
            add(i, t, 1);
            add(t, i, 0);
            ++N0;
        }
    }
    int ans = 0;
    while (bfs()) ans += dinic(s, 1e9);
    int n1 = ans, n0 = ans;
    ans += (N1 - n1) / 2 * 2, ans += (N0 - n0) / 2 * 2;
    n1 += (N1 - n1) / 2 * 2, n0 += (N0 - n0) / 2 * 2;
    if (n0 != N0)
        ans += 3;
    cout << ans;
}
