#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int inf = 1e9;
struct SegmentTree {
    std::vector<std::pair<int, int>> rMax, max;
    std::vector<int> tag, arMax;
    SegmentTree(int n) : rMax(4 * n), max(4 * n, {-inf, -1}), tag(4 * n), arMax(4 * n, -1) {}
    void build(int p, int l, int r, const std::vector<int> &s, const std::vector<int> &v) {
        if (r - l == 1) {
            rMax[p] = {v[s[l]], l};
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, s, v);
        build(2 * p + 1, m, r, s, v);
        rMax[p] = std::max(rMax[2 * p], rMax[2 * p + 1]);
    }
    std::pair<int, int> rangeRMax(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {-1, -1};
        }
        if (l >= x && r <= y) {
            return rMax[p];
        }
        int m = (l + r) / 2;
        return std::max(rangeRMax(2 * p, l, m, x, y), rangeRMax(2 * p + 1, m, r, x, y));
    }
    void push(int p) {
        add(2 * p, tag[p]);
        add(2 * p + 1, tag[p]);
        tag[p] = 0;
    }
    void add(int p, int v) {
        tag[p] += v;
        max[p].first += v;
    }
    void pull(int p) {
        max[p] = std::max(max[2 * p], max[2 * p + 1]);
    }
    int search(int p, int l, int r, int x) {
        if (r - l == 1) {
            return arMax[p] > x ? l : r;
        }
        int m = (l + r) / 2;
        if (arMax[2 * p] > x) {
            return search(2 * p, l, m, x);
        } else {
            return search(2 * p + 1, m, r, x);
        }
    }
    void activate(int p, int l, int r, int x, int v) {
        if (r - l == 1) {
            max[p] = {v, x};
            arMax[p] = rMax[p].first;
            rMax[p] = {-1, -1};
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            activate(2 * p, l, m, x, v);
        } else {
            activate(2 * p + 1, m, r, x, v);
        }
        pull(p);
        arMax[p] = std::max(arMax[2 * p], arMax[2 * p + 1]);
        rMax[p] = std::max(rMax[2 * p], rMax[2 * p + 1]);
    }
    void remove(int p, int l, int r, int x) {
        if (r - l == 1) {
            max[p] = {-inf, -1};
            arMax[p] = -1;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            remove(2 * p, l, m, x);
        } else {
            remove(2 * p + 1, m, r, x);
        }
        pull(p);
        arMax[p] = std::max(arMax[2 * p], arMax[2 * p + 1]);
    }
    void rangeAdd(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            add(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
};
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> l(q), r(q), p(q);
    for (int i = 0; i < q; i++) {
        std::cin >> l[i] >> r[i];
        l[i]--;
    }
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return l[i] < l[j];
    });
    std::vector<int> ans(q);
    SegmentTree segt(q);
    Fenwick<int> fen(n);
    for (int i = 0; i < n; i++) {
        fen.add(i, 1);
    }
    std::vector<int> s(n);
    std::iota(s.begin(), s.end(), 0);
    std::sort(s.begin(), s.end(), [&](int i, int j) {
        return a[i] > a[j];
    });
    std::set<int> act{-1, q};
    auto update = [&](int L, int R) {
        while (true) {
            int x = segt.rangeRMax(1, 0, q, L, R).second;
            if (x != -1 && (L == 0 || r[p[x]] >= r[p[L - 1]])) {
                segt.activate(1, 0, q, x, fen.rangeSum(l[p[x]], r[p[x]]));
                act.insert(x);
            } else {
                return;
            }
            R = x;
        }
    };
    segt.build(1, 0, q, p, r);
    update(0, n);
    for (int x = n, i = 0; x >= 0; x--) {
        while (i < n && a[s[i]] >= x) {
            int r = std::upper_bound(p.begin(), p.end(), s[i], [&](int i, int j) {
                return i < l[j];
            }) - p.begin();
            int l = segt.search(1, 0, q, s[i]);
            segt.rangeAdd(1, 0, q, l, r, -1);
            fen.add(s[i], -1);
            i++;
        }
        while (segt.max[1].first >= x) {
            int j = segt.max[1].second;
            segt.remove(1, 0, q, j);
            ans[p[j]] = x;
            act.erase(j);
            auto nxt = act.upper_bound(j);
            auto pre = std::prev(nxt);
            update(*pre + 1, *nxt);
        }
    }
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}
