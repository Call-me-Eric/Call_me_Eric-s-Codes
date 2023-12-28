#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

typedef vector<long long> poly;
const long long mod = 998244353, g = 3;
const int maxn = 1000010;
unordered_map<int, poly> mp;
void dfs(int, const poly&);
void solve(int, int, int);
char ans[maxn];
int n, N = 1;

int main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    int k;
    scanf("%d %d", &n, &k);
    int tmp = n;
    for (int i = 2; i <= n; i++)
        if (!(tmp % i)) {
            while (!(tmp % i)) tmp /= i;
            N *= i;
        }
    if (N == n) {
        int p, mx = -1;
        for (int i = 2; i <= n; i++)
            if (!(n % i)) {
                int cur = k / i * i;
                if (mx < cur) p = i, mx = cur;
            }
        for (int i = 0; i < n; i++)
            putchar('0' + (i % (n / p) < k / p));
        putchar('\n');
        return 0;
    }
    poly F(N + 1);
    auto gcd = [](int x, int y) {
        while (x %= y) swap(x, y);
        return y;
    };
    for (int i = 0; i <= N; i++) F[i] = gcd(i, N) != 1;
    dfs(n / N, F);
    while (!mp[n / N][k]) k--;
    solve(0, n / N - 1, k), printf("%s\n", ans);
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}

int tr[maxn << 2];
inline void ntt(const int l, poly& a, const bool f) {
    a.resize(l);
    for (int i = 0; i < l; i++)
        if (i < tr[i])
            swap(a[i], a[tr[i]]);
    for (int i = 2; i <= l; i <<= 1) {
        long long w = power(g, f ? (mod - 1) / i : mod - 1 - (mod - 1) / i);
        for (int j = 0; j < l; j += i) {
            long long pw = 1;
            for (int k = j; k < j + (i >> 1); k++) {
                long long x = a[k], y = a[k + (i >> 1)];
                a[k] = (x + y * pw) % mod;
                a[k + (i >> 1)] = (x - y * pw) % mod;
                pw = pw * w % mod;
            }
        }
    }
    if (!f) {
        long long I = power(l, mod - 2);
        for (auto& x : a) x = x * I % mod;
    }
    return;
}

poly mul(poly a, poly b) {
    int len = a.size() + b.size() - 1, L = 1;
    while (L <= len) L <<= 1;
    for (int i = 1; i < L; i++)
        tr[i] = tr[i >> 1] >> 1 | (i & 1 ? L >> 1 : 0);
    ntt(L, a, true), ntt(L, b, true);
    poly ret(L);
    for (int i = 0; i < L; i++) ret[i] = a[i] * b[i] % mod;
    ntt(L, ret, false), ret.resize(len);
    for (auto& x : ret) x = x != 0;
    return ret;
}

void dfs(const int n, const poly& F) {
    if (mp.count(n)) return;
    if (n == 1) {
        mp[n] = F;
        return;
    }
    dfs(n >> 1, F), dfs((n + 1) >> 1, F);
    mp[n] = mul(mp[n >> 1], mp[(n + 1) >> 1]);
    return;
}

void solve(const int l, const int r, const int k) {
    if (l == r) {
        int g = __gcd(k, N);
        for (int j = 0; j < N; j++)
            ans[(n / N) * j + l] = '0' + (j % (N / g) < k / g);
        return;
    }
    int mid = (l + r) >> 1;
    int L = mid - l + 1, R = r - mid;
    for (int x = 0; x <= k; x++)
        if (x < mp[L].size() && k - x < mp[R].size() && mp[L][x] && mp[R][k - x]) {
            solve(l, mid, x), solve(mid + 1, r, k - x);
            return;
        }
    return;
}
