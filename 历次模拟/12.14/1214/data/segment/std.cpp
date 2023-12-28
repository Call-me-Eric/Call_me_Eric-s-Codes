#include <bits/stdc++.h>
#define MAXN ((int) 2e5)
#define INF ((long long) 1e18)
using namespace std;
typedef pair<int, int> pii;
typedef pair<long long, pii> plii;

int n, A[MAXN + 10];
long long ans;

long long f[MAXN * 4 + 10][2][2];

// 套递归方程，更新线段树上的 f 值
void update(int id) {
    int nxt = id << 1;
    for (int i = 0; i <= 1; i++) for (int j = 0; j <= 1; j++) {
        f[id][i][j] = INF;
        for (int k = 0; k <= 1; k++) f[id][i][j] = min(f[id][i][j], max(f[nxt][i][k], f[nxt | 1][k][j]));
    }
}

// 构建线段树
void build(int id, int l, int r) {
    if (l == r) {
        // 递归方程初值
        f[id][0][0] = A[l];
        f[id][0][1] = l < n ? A[l] + A[l + 1] : INF;
        f[id][1][0] = l > 1 ? -INF : INF;
        f[id][1][1] = INF;
    } else {
        int nxt = id << 1, mid = (l + r) >> 1;
        build(nxt, l, mid);
        build(nxt | 1, mid + 1, r);
        update(id);
    }
}

// 把以 pos 为起点，len 为长度的线段的价值改成 +INF
void modify(int id, int l, int r, int pos, int len) {
    if (l == r) {
        if (len == 1) f[id][0][0] = INF;
        else f[id][0][1] = INF;
    } else {
        int nxt = id << 1, mid = (l + r) >> 1;
        if (pos <= mid) modify(nxt, l, mid, pos, len);
        else modify(nxt | 1, mid + 1, r, pos, len);
        update(id);
    }
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);

    build(1, 1, n);
    // 将所有线段的价值排序，以便枚举最小价值
    vector<plii> vec;
    for (int i = 1; i <= n; i++) vec.push_back(plii(A[i], pii(i, 1)));
    for (int i = 1; i < n; i++) vec.push_back(plii(A[i] + A[i + 1], pii(i, 2)));
    sort(vec.begin(), vec.end());

    ans = INF;
    // 枚举最小价值
    for (plii p : vec) {
        ans = min(ans, f[1][0][0] - p.first);
        modify(1, 1, n, p.second.first, p.second.second);
    }
    printf("%lld\n", ans);
}

int main() {
    int tcase=1;
    while (tcase--) solve();
    return 0;
}
