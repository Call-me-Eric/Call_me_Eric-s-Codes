#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int N = 500;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    i64 n;
    std::cin >> n;
    std::vector<int> xy(N, -1), yx(N, -1);
    std::vector<bool> ans(N);
    ans[0] = true;
    int cnt = 0;
    for (int i = 0; i + 1 < N && i < n; i++) {
        std::vector<bool> vis(N);
        std::function<bool(int)> dfsx = [&](int x) {
            vis[x] = true;
            for (int y = 0; y < i; y++) {
                if ((n - y) % (x + 1) == 0) {
                    if (yx[y] == -1 || (!vis[yx[y]] && dfsx(yx[y]))) {
                        xy[x] = y; 
                        yx[y] = x;
                        return true;
                    }
                }
            }
            return false;
        };
        cnt += dfsx(i);
        vis.assign(N, false);
        std::function<bool(int)> dfsy = [&](int y) {
            vis[y] = true;
            for (int x = 0; x <= i; x++) {
                if ((n - y) % (x + 1) == 0) {
                    if (xy[x] == -1 || (!vis[xy[x]] && dfsy(xy[x]))) {
                        xy[x] = y;
                        yx[y] = x;
                        return true;
                    }
                }
            }
            return false;
        };
        cnt += dfsy(i);
        ans[i + 1] = (cnt == i + 1);
    }
    if (2 * (N - 1) >= n) {
        std::cout << "2\n";
        std::cout << n + 1;
        for (int i = 0; i <= n; i++) {
            std::cout << " " << (i < N ? ans[i] : ans[n - i]);
        }
        std::cout << "\n";
    } else {
        std::cout << "61\n";
        std::cout << "2 0 0\n";
        for (int i = 2; i <= 59; i++) {
            std::cout << 2 << " " << i << " " << i << "\n";
        }
        std::vector<int> x;
        for (int i = 0; i < N; i++) {
            x.push_back(ans[i]);
        }
        i64 r = n - 2 * N + 1;
        for (int i = 0; i < 60; i++) {
            if (r >> i & 1) {
                x.push_back(i == 0 ? 0 : i + 1);
            }
        }
        for (int i = N - 1; i >= 0; i--) {
            x.push_back(ans[i]);
        }
        std::cout << x.size();
        for (auto a : x) {
            std::cout << " " << a;
        }
        std::cout << "\n";
    }
    return 0;
}
