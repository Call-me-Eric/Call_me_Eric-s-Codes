#include <bits/stdc++.h>

int main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    for (int i = k; i >= 1; --i) {
        int g = std::__gcd(i, n);
        if (g != 1) {
            int t1 = i / g, t0 = (n - i) / g;
            for (int j = 1; j <= g; ++j) {
                std::cout << std::string(t1, '1') << std::string(t0, '0');
            }
            std::cout << '\n';
            return 0;
        }
    }

    std::cout << std::string(n, '0') << '\n';

    return 0;
}
