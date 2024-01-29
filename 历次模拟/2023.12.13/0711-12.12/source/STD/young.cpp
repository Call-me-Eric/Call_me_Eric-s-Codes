#include <bits/stdc++.h>
using namespace std;

constexpr int P = 998244353;

template <class T> T qp(T a, int b) {
    T c{1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            c *= a;
        }
    }
    return c;
}

struct mint {
    int x;
    mint(int _x = 0) : x(_x % P) { x < 0 ? x += P : 0; }
    int val() const { return x; }

    mint operator - () const {
        return -x;
    }
    mint inv() const {
        assert(x != 0);
        return qp(*this, P - 2);
    }
    mint &operator += (const mint &rhs) {
        x += rhs.x - P, x += x >> 31 & P;
        return *this;
    }
    mint &operator -= (const mint &rhs) {
        x -= rhs.x, x += x >> 31 & P;
        return *this;
    }
    mint &operator *= (const mint &rhs) {
        x = (long long)x * rhs.x % P;
        return *this;
    }
    mint &operator /= (const mint &rhs) {
        return *this *= rhs.inv();
    }
    friend mint operator + (mint lhs, const mint &rhs) {
        return lhs += rhs;
    }
    friend mint operator - (mint lhs, const mint &rhs) {
        return lhs -= rhs;
    }
    friend mint operator * (mint lhs, const mint &rhs) {
        return lhs *= rhs;
    }
    friend mint operator / (mint lhs, const mint &rhs) {
        return lhs /= rhs;
    }

    friend ostream &operator << (ostream &os, const mint &a) {
        return os << a.val();
    }
};

struct _comb {
    int n;
    vector<mint> _fact, _finv, _inv;

    _comb() : n{0}, _fact{1}, _finv{1}, _inv{0} {}
    _comb(int n) : _comb() { init(n); }

    void init(int m) {
        if (m <= n) return;
        _fact.resize(m + 1);
        _finv.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fact[i] = _fact[i - 1] * i;
        }
        _finv[m] = _fact[m].inv();
        for (int i = m; i > n; i--) {
            _finv[i - 1] = _finv[i] * i;
            _inv[i] = _finv[i] * _fact[i - 1];
        }
        n = m;
    }

    mint fact(int m) {
        if (m > n) init(2 * m);
        return _fact[m];
    }
    mint finv(int m) {
        if (m > n) init(2 * m);
        return _finv[m];
    }
    mint inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    mint binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fact(n) * finv(m) * finv(n - m);
    }
} comb; 

int main() {
    freopen("young.in", "r", stdin);
    freopen("young.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) {
        cin >> x;
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int &x : b) {
        cin >> x;
    }
    int l = max(n, m) + 1;
    a.resize(l);
    b.resize(l);
    auto solve = [&](auto a) {
        int sum = accumulate(a.begin(), a.end(), 0);
        vector<map<vector<int>, mint>> dp(sum + 1);
        dp[sum][a] = 1;
        for (int s = sum; s; s--) {
            for (auto [_, w] : dp[s]) {
                auto a = _;
                for (int i = 0; i + 1 < a.size(); i++) {
                    if (a[i] > a[i + 1]) {
                        a[i]--;
                        dp[s - 1][a] += w;
                        a[i]++;
                    }
                }
            }
        }
        return dp;
    };
    auto sub_a = solve(a), sub_b = solve(b);
    int sa = sub_a.size() - 1, sb = sub_b.size() - 1;
    vector<mint> fact((int)1e7 + 5);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++) {
        fact[i] = fact[i - 1] * (2 * i - 1);
    }
    vector<mint> sum(min(sa, sb) + 1);
    for (int i = 0; i <= min(sa, sb); i++) {
        for (auto [a, w] : sub_a[i]) {
            if (sub_b[i].count(a)) {
                sum[i] += w * sub_b[i][a];
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        if ((sa + sb + k) % 2) {
            cout << "0\n";
            continue;
        }
        mint ans;
        for (int i = 0; i <= min(sa, sb); i++) {
            int _k = k - (sa - i + sb - i);
            if (_k < 0) continue;
            ans += sum[i] * fact[_k / 2] * comb.binom(k, _k) * comb.binom(sa - i + sb - i, sa - i);
        }
        cout << ans << "\n";
    }
    return 0;
}