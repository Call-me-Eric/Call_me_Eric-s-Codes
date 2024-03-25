#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<std::pair<int, int>> a;
    if (n % 2 == 0) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n / 2; j++) {
                if (j == 0) {
                    a.emplace_back(n - 1, i);
                } else {
                    a.emplace_back((i - j + n - 1) % (n - 1), (i + j) % (n - 1));
                }
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n / 2; j++) {
                a.emplace_back((i - j + n) % n, (i + j) % n);
            }
        }
    }
    int ans = (a.size() + k - 1) / k;
    std::cout << ans << "\n";
    for (int i = 0; i < ans; i++) {
        int r = std::min(int(a.size()), (i + 1) * k);
        std::cout << r - i * k << "\n";
        for (int j = i * k; j < r; j++) {
            std::cout << a[j].first + 1 << " " << a[j].second + 1 << "\n";
        }
    }
    return 0;
}
