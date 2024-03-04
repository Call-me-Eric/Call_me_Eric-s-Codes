#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL N = 300000, B = 450;
using namespace std;
LL n, cq, a[N + 9], p[N + 9];
vector<pair<LL, LL>> q[N + 9];

LL bel[N + 9], bl[N + 9], br[N + 9], cb;
LL val[N + 9], sum[N + 9];

void Build() {
    for (int i = 1; i <= n; ++i) val[i] = sum[i] = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(l + B - 1, n);
        bl[++cb] = l;
        br[cb] = r;
        for (int i = l; i <= r; ++i) bel[i] = cb;
    }
}

void Add(int p) {
    ++val[p];
    ++sum[bel[p]];
}

LL Query(int p) {
    LL b = bel[p], res = 0;
    for (int i = p; i <= br[b]; ++i) res += val[i];
    for (int i = b + 1; i <= cb; ++i) res += sum[i];
    return res;
}

LL ans[N + 9];

void MAIN() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        q[i].clear();
        cin >> a[i];
        p[a[i]] = i;
    }
    cin >> cq;
    //  cout << cq << endl;
    for (int i = 1; i <= cq; ++i) {
        int l, r;
        cin >> l >> r;
        q[r].emplace_back(l, i);
    }
    Build();
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        for (int j = 1; j * j <= n << 1; ++j) {
            int y = j * j - x;
            if (y >= 1 && y <= n && p[y] < i) Add(p[y]);
        }
        for (auto nd : q[i]) {
            int l = nd.first;
            int id = nd.second;
            ans[id] = Query(l);
        }
    }
    for (int i = 1; i <= cq; ++i) cout << ans[i] << '\n';
}

int main() {
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    MAIN();
    return 0;
}