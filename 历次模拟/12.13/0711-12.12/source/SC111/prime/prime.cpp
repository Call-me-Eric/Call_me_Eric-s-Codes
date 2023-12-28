#include <bits/stdc++.h>
constexpr int P = 998244353;
using ull = unsigned long long;

constexpr int Z = 10, N = 18;
std::vector<std::array<int, 2>> E[Z];

int calc(std::string s) {
    std::array<std::array<int, N>, 2> f {};
    f[0][0] = 1;

    for (char c : s) {
        std::array<std::array<ull, N>, 2> g {};
        int x = c - '0';
        for (int t : { 0, 1 }) {
            for (int y = 0; y < Z; y++) {
                if (!t && y > x) {
                    continue;
                }
                int nt = (t | (y < x));
                for (auto &[u, v] : E[y]) {
                    g[nt][v] += f[t][u];
                }
            }
        }

        for (int t : { 0, 1 }) {
            for (int i = 0; i < N; i++) {
                f[t][i] = g[t][i] % P;
            }
        }
    }

    ull ans = 0;
    for (int t : { 0, 1 }) {
        for (int i = 0; i < N; i++) {
            ans += f[t][i];
        }
    }
    return ans % P;
}

int main() {
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    E[0].push_back({ 0, 0 });
    E[0].push_back({ 1, 1 });
    E[0].push_back({ 2, 6 });
    E[0].push_back({ 3, 1 });
    E[0].push_back({ 4, 2 });
    E[0].push_back({ 5, 3 });
    E[0].push_back({ 6, 6 });
    E[0].push_back({ 7, 7 });
    E[0].push_back({ 8, 6 });
    E[0].push_back({ 9, 1 });
    E[0].push_back({ 10, 6 });
    E[0].push_back({ 11, 9 });
    E[0].push_back({ 12, 16 });
    E[0].push_back({ 13, 6 });
    E[0].push_back({ 14, 11 });
    E[0].push_back({ 15, 6 });
    E[0].push_back({ 16, 14 });
    E[0].push_back({ 17, 14 });
    E[1].push_back({ 0, 6 });
    E[1].push_back({ 2, 6 });
    E[1].push_back({ 3, 6 });
    E[1].push_back({ 4, 6 });
    E[1].push_back({ 5, 6 });
    E[1].push_back({ 7, 6 });
    E[4].push_back({ 0, 15 });
    E[4].push_back({ 1, 6 });
    E[4].push_back({ 2, 6 });
    E[4].push_back({ 3, 6 });
    E[4].push_back({ 4, 6 });
    E[4].push_back({ 5, 13 });
    E[4].push_back({ 6, 6 });
    E[4].push_back({ 7, 6 });
    E[4].push_back({ 8, 6 });
    E[4].push_back({ 9, 8 });
    E[4].push_back({ 10, 6 });
    E[4].push_back({ 11, 8 });
    E[4].push_back({ 12, 8 });
    E[4].push_back({ 13, 6 });
    E[4].push_back({ 14, 8 });
    E[4].push_back({ 15, 6 });
    E[4].push_back({ 16, 8 });
    E[4].push_back({ 17, 8 });
    E[6].push_back({ 0, 12 });
    E[6].push_back({ 1, 1 });
    E[6].push_back({ 2, 6 });
    E[6].push_back({ 3, 1 });
    E[6].push_back({ 4, 6 });
    E[6].push_back({ 5, 1 });
    E[6].push_back({ 6, 6 });
    E[6].push_back({ 7, 6 });
    E[6].push_back({ 8, 6 });
    E[6].push_back({ 9, 1 });
    E[6].push_back({ 10, 8 });
    E[6].push_back({ 11, 1 });
    E[6].push_back({ 12, 17 });
    E[6].push_back({ 13, 10 });
    E[6].push_back({ 14, 1 });
    E[6].push_back({ 15, 15 });
    E[6].push_back({ 16, 1 });
    E[6].push_back({ 17, 14 });
    E[8].push_back({ 0, 7 });
    E[8].push_back({ 1, 6 });
    E[8].push_back({ 2, 6 });
    E[8].push_back({ 3, 2 });
    E[8].push_back({ 4, 6 });
    E[8].push_back({ 5, 4 });
    E[8].push_back({ 6, 6 });
    E[8].push_back({ 7, 6 });
    E[8].push_back({ 8, 6 });
    E[8].push_back({ 9, 6 });
    E[8].push_back({ 10, 6 });
    E[8].push_back({ 11, 6 });
    E[8].push_back({ 12, 6 });
    E[8].push_back({ 13, 6 });
    E[8].push_back({ 14, 6 });
    E[8].push_back({ 15, 6 });
    E[8].push_back({ 16, 6 });
    E[8].push_back({ 17, 6 });
    E[9].push_back({ 0, 5 });
    E[9].push_back({ 1, 1 });
    E[9].push_back({ 3, 1 });
    E[9].push_back({ 5, 1 });
    E[9].push_back({ 8, 6 });
    E[9].push_back({ 9, 1 });
    E[9].push_back({ 10, 6 });
    E[9].push_back({ 11, 1 });
    E[9].push_back({ 12, 1 });
    E[9].push_back({ 13, 6 });
    E[9].push_back({ 14, 1 });
    E[9].push_back({ 15, 6 });
    E[9].push_back({ 16, 1 });
    E[9].push_back({ 17, 1 });

    int T;
    std::cin >> T;
    while (T--) {
        std::string l, r;
        std::cin >> l >> r;
        int pos = l.find_last_not_of('0');
        l[pos]--;
        std::fill(l.begin() + pos + 1, l.end(), '9');
        std::cout << (calc(r) - calc(l) + P) % P << "\n";
    }

    return 0;
}