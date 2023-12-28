#include "bits/stdc++.h"
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include "PrettyDebug.hpp"
#else
#define debug(...)
#endif
#define For(i, a, b) for (int i = a; i <= b; i++)
#define Rev(i, a, b) for (int i = a; i >= b; i--)
#define Fin(file) freopen(file, "r", stdin)
#define Fout(file) freopen(file, "w", stdout)
#define assume(expr) \
    ((!!(expr)) ||   \
     (exit((fprintf(stderr, "Assumption Failed: %s on Line %d\n", #expr, __LINE__), -1)), false))
#define range basic_string_view
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
signed main() {
    freopen("horse.in", "r", stdin);
    freopen("horse.out", "w", stdout);
    atexit([]() { cerr << "Time = " << clock() << " ms" << endl; });
    auto find = [&](int n, int m, pii S, pii T) {
        auto ck = [&](int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; };
        deque<pii> q;
        vector vis(n + 1, vector(m + 1, 0));
        function<bool(int, int)> dfs = [&](int x, int y) {
            q.emplace_back(x, y);
            vis[x][y] = 1;
            if (pii(x, y) == T)
                return q.size() != 1u * n * m ? q.pop_back(), vis[x][y] = 0, false : true;
            if (q.size() == 1u * n * m)
                return q.pop_back(), vis[x][y] = 0, false;
#define DO(u, v)                                                     \
    if (ck(x + u, y + v) && !vis[x + u][y + v] && dfs(x + u, y + v)) \
    return true
            DO(-2, -1);
            DO(-1, -2);
            DO(-2, 1);
            DO(1, -2);
            DO(2, -1);
            DO(-1, 2);
            DO(2, 1);
            DO(1, 2);
            q.pop_back();
            vis[x][y] = 0;
            return false;
        };
        dfs(S.first, S.second);
        return q;
    };
    vector q(8, deque<pii>());
    for (int m : { 3, 5, 7 }) {
        For(i, 1, 4) For(j, 1, m) if (minmax(abs(i - 2), abs(j - m - 1)) == minmax(1, 2)) {
            For(x, 1, 4) For(y, 1, m) if (minmax(abs(x - 3), abs(y - m - 1)) == minmax(1, 2)) {
                auto tmp = find(4, m, pii(i, j), pii(x, y));
                if (tmp.size()) {
                    q[m] = tmp;
                    cerr << "Success " << m << '\n';
                    goto DONE;
                }
            }
        }
    DONE:
        if (q[m].empty())
            cerr << "Failed " << m << '\n';
    }
    auto solve = [&](int m) {
        if (m == 1 || m == 2 || m == 4)
            return deque<pii>();
        int x = m % 3 == 0 ? 3 : m % 3 == 1 ? 7 : 5;
        auto a = q[x];
        int flg = 0;
        while (x < m) {
            if (flg == 0) {
                a.emplace_front(2, x + 1);
                a.emplace_back(3, x + 1);
                a.emplace_front(4, x + 2);
                a.emplace_back(1, x + 2);
                a.emplace_front(2, x + 3);
                a.emplace_back(3, x + 3);
                a.emplace_front(1, x + 1);
                a.emplace_back(4, x + 1);
                a.emplace_front(3, x + 2);
                a.emplace_back(2, x + 2);
                a.emplace_front(1, x + 3);
                a.emplace_back(4, x + 3);
            } else {
                a.emplace_back(2, x + 1);
                a.emplace_front(3, x + 1);
                a.emplace_back(4, x + 2);
                a.emplace_front(1, x + 2);
                a.emplace_back(2, x + 3);
                a.emplace_front(3, x + 3);
                a.emplace_back(1, x + 1);
                a.emplace_front(4, x + 1);
                a.emplace_back(3, x + 2);
                a.emplace_front(2, x + 2);
                a.emplace_back(1, x + 3);
                a.emplace_front(4, x + 3);
            }
            x += 3;
            flg ^= 1;
        }
        return a;
    };
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> m;
        auto ans = solve(m);
        if (ans.empty())
            cout << "No\n";
        else {
            cout << "Yes\n";
            for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
            assume(ans.size() == 4u * m);
            For(i, 0, 4 * m - 2) if (minmax(abs(ans[i].first - ans[i + 1].first),
                                            abs(ans[i].second - ans[i + 1].second)) != minmax(1, 2)) cerr
                << "Error on " << i << '\n',
                exit(1);
        }
    }
    return 0;
}