#include <bits/stdc++.h>
const int mod = 1e9 + 7;
using namespace std;
int n, a[500001], st[2][20][500001], f[500001], L[500001], R[500001], sum[500001], tr[500001];
inline int check(int op, int x, int y) {
    if (op == 0) {
        if (a[x] > a[y])
            return x;
        return y;
    }
    if (a[x] > a[y])
        return y;
    return x;
}
inline int query(int op, int x, int y) {
    int k = log2(y - x + 1);
    return check(op, st[op][k][x], st[op][k][y - (1 << k) + 1]);
}
inline void update(int x, int y) {
    for (; x <= n; x += (x & (-x))) tr[x] = (tr[x] + y) % mod;
}
inline int query(int x) {
    int ans = 0;
    for (; x; x -= (x & (-x))) ans = (ans + tr[x]) % mod;
    return ans;
}
inline void solve(int l, int r) {
    if (l > r)
        return;
    if (l == r) {
        f[l] = (f[l] + query(l)) % mod;
        if (a[l] == 1)
            f[l] = (f[l] + f[l - 1]) % mod;
        sum[l] = (sum[l - 1] + f[l]) % mod;
        return;
    }
    int mid = query(0, l, r);
    solve(l, mid - 1);
    if (mid - l > r - mid) {
        for (int i = mid; i <= r; ++i) {
            int s = max(l, i - a[mid] + 1);
            int t = min(L[i], mid);
            if (s <= t) {
                if (s >= 2)
                    f[i] = ((f[i] + sum[t - 1]) % mod - sum[s - 2]) % mod;
                else
                    f[i] = (f[i] + sum[t - 1]) % mod;
            }
        }
    } else {
        for (int i = l; i <= mid; ++i) {
            int s = max(mid, R[i]);
            int t = min(r, i + a[mid] - 1);
            if (s <= t && i - 1) {
                update(s, f[i - 1]);
                if (t != n)
                    update(t + 1, -f[i - 1]);
            }
        }
    }
    f[mid] = (f[mid] + query(mid)) % mod;
    sum[mid] = (sum[mid - 1] + f[mid]) % mod;
    solve(mid + 1, r);
}
int main() {
    freopen("safpar.in","r",stdin);
    freopen("safpar.out","w",stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        st[0][0][i] = st[1][0][i] = i;
    }
    for (int i = 1; i <= 19; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            st[0][i][j] = check(0, st[0][i - 1][j], st[0][i - 1][j + (1 << (i - 1))]),
            st[1][i][j] = check(1, st[1][i - 1][j], st[1][i - 1][j + (1 << (i - 1))]);
    int now = 0;
    for (int i = 1; i <= n; ++i) {
        while (now + 1 <= i && a[query(1, now + 1, i)] <= i - now) ++now;
        L[i] = now;
        if (now && a[query(0, 1, i)] >= i)
            f[i] = 1;
        // cout<<f[i]<<endl;
    }
    now = n + 1;
    for (int i = n; i; --i) {
        while (now - 1 >= i && L[now - 1] >= i) --now;
        R[i] = now;
        // cout<<R[i]<<endl;
    }
    solve(1, n);
    cout << (f[n] + mod) % mod << endl;
}
