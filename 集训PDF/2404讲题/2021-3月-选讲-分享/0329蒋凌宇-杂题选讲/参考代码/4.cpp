#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353;
int power(int a, int b) {
    int res = 1;
    for (; b > 0; b /= 2, a = i64(a) * a % P) {
        if (b % 2 == 1) {
            res = i64(res) * a % P;
        }
    }
    return res;
}
int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        ans = ans / n * (n - 1);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    int ans = phi(n);
    for (int i = 0; i < k - 1; i++) {
        ans = i64(ans) * (n - 1 - i) % P;
    }
    int den = 1;
    for (int i = 1; i <= k - 1; i++) {
        den = i64(den) * i % P;
    }
    ans = i64(ans) * power(den, P - 2) % P;
    std::cout << ans << "\n";
    return 0;
}