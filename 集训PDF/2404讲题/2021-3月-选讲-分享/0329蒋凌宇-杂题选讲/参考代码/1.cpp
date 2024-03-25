#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int power(int a, int b, int c) {
    int res = 1;
    for (; b > 0; b /= 2, a = i64(a) * a % c) {
        if (b % 2 == 1) {
            res = i64(res) * a % c;
        }
    }
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int A, k;
    std::cin >> A >> k;
    int a0 = A;
    std::vector<int> c(k), x(k), y(k), z(k);
    int ans = 0;
    std::vector<int> last(k);
    for (int i = 0; i < k; i++) {
        std::cin >> c[i] >> x[i] >> y[i] >> z[i];
        for (int j = 0; j < c[i]; j++) {
            A = (i64(A) * x[i] + y[i]) % z[i];
        }
        last[i] = A;
    }
    int N = n;
    for (int i = k - 1; i >= 0; i--) {
        int v = last[i];
        int inv = power(x[i], z[i] - 2, z[i]);
        for (int j = 0; j < c[i]; j++) {
            if (v < m) {
                m--;
            } else if (N == m) {
                ans++;
                m--;
            }
            N--;
            v = i64(v - y[i] + z[i]) * inv % z[i];
        }
    }
    if (a0 >= 1 && m == 1) {
        ans++;
    }
    std::cout << ans << "\n";
    return 0;
}
