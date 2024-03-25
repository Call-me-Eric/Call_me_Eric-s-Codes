#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007;
int power(int a, int b) {
    int res = 1;
    for (; b > 0; b /= 2, a = i64(a) * a % P) {
        if (b % 2 == 1) {
            res = i64(res) * a % P;
        }
    }
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n - 1), sum(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> a[i];
        sum[i] = a[i];
        if (i > 0) {
            sum[i] += sum[i - 1];
        }
    }
    std::vector<int> pre(n), invpre(n), inv(n - 1);
    pre[0] = 1;
    for (int i = 0; i < n - 1; i++) {
        pre[i + 1] = i64(pre[i]) * sum[i] % P;
    }
    invpre[n - 1] = power(pre[n - 1], P - 2);
    for (int i = n - 2; i >= 0; i--) {
        invpre[i] = i64(invpre[i + 1]) * sum[i] % P;
        inv[i] = i64(invpre[i + 1]) * pre[i] % P;
    }
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    std::vector<int> d(n);
    d[0] = 0;
    for (int i = 1, s = 0; i < n; i++) {
        s = (s + i64(a[i - 1]) * (d[i - 1] + c[i - 1])) % P;
        d[i] = (c[i] + i64(s) * inv[i - 1]) % P;
    }
    std::vector<int> f(n - 1);
    for (int i = 0; i < n - 1; i++) {
        f[i] = i64(a[i]) * inv[i] % P;
    }
    std::vector<int> ans(n - 1);
    for (int i = 0, s = 0; i < n - 1; i++) {
        ans[i] = (i64(f[i]) * d[i] + i64(s) * (1 - f[i] + P)) % P;
        s = (i64(s) * (1 - i64(f[i]) * f[i] % P + P) + i64(f[i]) * f[i] % P * d[i]) % P;
    }
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        if (u == v) {
            std::cout << "0\n";
        } else {
            if (u > v) {
                std::swap(u, v);
            }
            std::cout << (d[u] + d[v] + 2ll * (P - ans[u])) % P << "\n";
        }
    }
    return 0;
}
