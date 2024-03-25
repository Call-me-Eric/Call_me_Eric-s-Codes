#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
        c[i]--;
    }
    std::vector<std::vector<int>> ans;
    std::vector<int> sum;
    auto add = [&](int id, int l, int len) {
        if (len == 0) {
            return;
        }
        std::reverse(c.begin() + l, c.begin() + l + len);
        if (int(ans.size()) == id) {
            ans.push_back({});
            sum.push_back(0);
        }
        while (sum[id] < l) {
            ans[id].push_back(1);
            sum[id]++;
        }
        ans[id].push_back(len);
        sum[id] += len;
    };
    std::function<void(int, int, int)> solve = [&](int l, int r, int id) {
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        while (true) {
            std::vector<int> a;
            if (c[l] >= m) {
                a.push_back(0);
            }
            for (int i = l; i < r; ) {
                int j = i;
                while (j < r && (c[i] < m) == (c[j] < m)) {
                    j++;
                }
                a.push_back(j - i);
                i = j;
            }
            if (a.size() == 2) {
                break;
            }
            int cur = l;
            for (int i = 0; i < int(a.size()); i += 3) {
                add(id, cur, a[i]);
                cur += a[i];
                if (i + 2 < int(a.size())) {
                    add(id, cur, a[i + 1] + a[i + 2]);
                    cur += a[i + 1] + a[i + 2];
                } else if (i + 1 < int(a.size())) {
                    add(id, cur, a[i + 1]);
                }
            }
            id++;
        }
        solve(l, m, id);
        solve(m, r, id);
    };
    solve(0, n, 0);
    for (int i = 0; i < int(ans.size()); i++) {
        while (sum[i] < n) {
            ans[i].push_back(1);
            sum[i]++;
        }
        if (i % 2 == 1) {
            std::reverse(ans[i].begin(), ans[i].end());
        }
    }
    if (ans.size() % 2 == 1) {
        ans.emplace_back(n, 1);
    }
    ans.erase(std::remove(ans.begin(), ans.end(), std::vector{n}), ans.end());
    std::cout << ans.size() << "\n";
    for (auto v : ans) {
        std::cout << v.size();
        for (auto x : v) {
            std::cout << " " << x;
        }
        std::cout << "\n";
    }
    return 0;
}
