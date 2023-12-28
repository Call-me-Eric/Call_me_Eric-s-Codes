#include <bits/stdc++.h>

#ifndef _STKLIB_DSU_HPP
# define _STKLIB_DSU_HPP

# include <cstddef>
# include <vector>
# include <numeric>

namespace StK {

class DSU {

   protected:
    std::vector<int> data;

   public:
    DSU(size_t n) : data(n, 0) { std::iota(data.begin(), data.end(), 0); }
    size_t find(size_t x) { return x == data[x] ? x : data[x] = find(data[x]); }
    size_t operator()(size_t x) { return find(x); }
    size_t operator[](size_t x) { return data[x]; }
    bool merge(size_t x, size_t y) { return (x = find(x)) != (y = find(y)) ? data[y] = x, true : false; }

};

} // namespace StK

#endif

int main() {
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    StK::DSU dsu(n);
    std::vector<std::pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        std::cin >> u >> v;
        --u, --v;
        dsu.merge(u, v);
    }
    
    std::vector<int> val(n);
    for (int i = 0; i < n; ++i) {
        ++val[dsu(i)];
    }

    for (auto [u, v] : edges) {
        --val[dsu[u]];
    }

    for (auto x : val) {
        if (x < 0) {
            std::cout << -1 << '\n';
            return 0;
        }
    }

    bool has_cyc = false;
    for (int i = 0; i < n; ++i) {
        if (dsu[i] == i) {
            if (val[i] == 0) {
                has_cyc = true;
            }
        }
    }
    
    if (!has_cyc) {
        int64_t ans = 0;
        val = std::vector<int>(n);
        for (int i = 0; i < n; ++i) {
            ++val[dsu[i]];
        }
        for (auto x : val) ans += int64_t(x) * (x + 1) / 2;
        std::cout << 0 << ' ' << ans << '\n';
        return 0;
    }
    
    std::vector<std::vector<int>> to(n);
    for (auto [u, v] : edges) {
        to[u].push_back(v);
        to[v].push_back(u);
    }

    std::vector<int> nodes_num(n);
    for (int i = 0; i < n; ++i) {
        ++nodes_num[dsu[i]];
    }

    long double ans = 0;
    std::vector<int> ban(n), vis(n);
    for (int i = 0; i < n; ++i) {
        if (dsu[i] != i) {
            continue;
        }
        if (val[i] == 1) {
            continue;
        }

        std::vector<int> cyc;
        {
            std::vector<int> sta;
            auto _F_dfs = [&](auto self, int u, int fa) -> void {
                sta.push_back(u);
                vis[u] = true;
                for (auto v : to[u]) {
                    if (v == fa) {
                        continue;
                    }
                    if (vis[v]) {
                        cyc = std::vector<int>(
                            std::find(sta.begin(), sta.end(), v),
                            sta.end()
                        );
                        return;
                    }
                    self(self, v, u);
                    if (cyc.size()) {
                        return;
                    }
                }
                sta.pop_back();
            };
            _F_dfs(_F_dfs, i, i);
            assert(cyc.size());
        }
        for (auto u : cyc) {
            ban[u] = 1;
        }

        int s = nodes_num[i];
        int k = cyc.size();

        ans += (long double)(s * int64_t(s)) / k;
        
        // std::vector<std::vector<int>> num(k);

        // MInt ans;
        // auto self = [&]() {
        //     Poly fl(k), fr(k);
        //     for (int i = 0; i < k; ++i) {
        //         int u = cyc[i];
                
        //         auto _F_dfs = [&](auto self, int u, int fa, int d) -> void {
        //             if (d == num[i].size()) {
        //                 num[i].push_back(1);
        //             } else {
        //                 ++num[i][d];
        //             }
        //             for (auto v : to[u]) if (v != fa && !ban[v]) {
        //                 self(self, v, u, d + 1);
        //             }
        //         };
        //         _F_dfs(_F_dfs, u, u, 0);

        //         int s = num[i].size();
        //         for (int j = 0; j < s; ++j) {
        //             fl[((i - j) % k + k) % k] += num[i][j];
        //             fr[((i + j) % k + k) % k] += num[i][j];
        //         }
        //     }

        //     std::reverse(fr.begin(), fr.end());
        // };

    }

    std::cout << 1 << ' ' << int64_t(ans) << '\n';

    return 0;
}
