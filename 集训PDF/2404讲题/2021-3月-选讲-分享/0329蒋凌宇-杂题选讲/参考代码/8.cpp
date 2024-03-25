#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

constexpr int inf = 1e9 + 1;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> v{ -inf };
    v.reserve(2 * n + 1);
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> l[i] >> r[i];
        ++r[i];
        v.push_back(l[i]);
        v.push_back(r[i]);
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    int m = v.size();
    std::vector<int> mx(m), mn(m, m);
    for (int i = 0; i < n; ++i) {
        l[i] = std::lower_bound(v.begin(), v.end(), l[i]) - v.begin();
        r[i] = std::lower_bound(v.begin(), v.end(), r[i]) - v.begin();
        mx[l[i]] = std::max(mx[l[i]], r[i]);
        mn[l[i] - 1] = std::min(mn[l[i] - 1], r[i]);
    }
    for (int i = 1; i < m; ++i) {
        mx[i] = std::max(mx[i], mx[i - 1]);
    }
    for (int i = m - 2; i >= 0; --i) {
        mn[i] = std::min(mn[i], mn[i + 1]);
    }
    std::vector<int> pts;
    for (int i = m - 1, j = m - 1; i >= 0; --i) {
        if (mn[i] <= j) {
            pts.push_back(i + 1);
            j = i + 1;
        }
    }
    std::reverse(pts.begin(), pts.end());
    int t = 0;
    for (int i = 0; i < n; ++i) {
        int q = std::lower_bound(pts.begin(), pts.end(), r[i]) - std::lower_bound(pts.begin(), pts.end(), l[i]);
        t = std::max(t, q);
    }
    if (t > 1) {
        int lg = std::__lg(t - 1);
        std::vector<std::vector<int>> f(m, std::vector<int>(lg + 1, -1));
        for (int i = 0; i <= lg; ++i) {
            f[m - 1][i] = m - 1;
        }
        for (int i = m - 2, j = m - 1; i >= 0; --i) {
            while ((j >= mn[i] || f[j][0] == -1) && j > i) {
                --j;
            }
            if (i == j) {
                break;
            }
            int x = t - 2, u = j;
            for (int k = lg; k >= 0; --k) {
                if (x >> k & 1) {
                    u = f[u][k];
                }
            }
            if (mx[i] <= u) {
                f[i][0] = j;
                for (int k = 0; k < lg; ++k) {
                    f[i][k + 1] = f[f[i][k]][k];
                }
            }
        }
        if (f[0][0] != -1) {
            --t;
            pts.clear();
            for (int i = f[0][0]; i < m - 1; i = f[i][0]) {
                pts.push_back(i);
            }
        }
    }
    std::cout << t << " " << pts.size();
    for (auto x : pts) {
        std::cout << " " << v[x];
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}