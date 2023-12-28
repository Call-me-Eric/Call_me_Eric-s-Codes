/*
 *@author:Ayersz127
 *@time: 2023-05-20
 */
#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

constexpr int N = 2e5 + 5;
constexpr int P = 998244353;

template <typename T>
T pow(T x, T y) {
    T ret = 1;
    while (y) {
        if (y & 1) {
            ret = i64(ret) * x % P;
        }
        x = i64(x) * x % P;
        y >>= 1;
    }
    return ret;
}

int inv(int x) {
    return pow(x, P - 2);
}

int n;
int fac[N], ifac[N];
int ipow2[N];
int sum[N];

int binom(int x, int y) {
    return i64(fac[x]) * ifac[y] % P * ifac[x - y] % P;
}

int main() {
    freopen("subseq.in", "r", stdin);
    freopen("subseq.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int inv2 = inv(2);
    ipow2[0] = 1;
    for (int i = 1; i < N; i++) {
        ipow2[i] = i64(ipow2[i - 1]) * inv2 % P;
    }
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = i64(fac[i - 1]) * i % P;
    }
    ifac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        ifac[i] = i64(ifac[i + 1]) * (i + 1) % P;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> s; n=s.size();
        s = "#" + s;
        vector<int> f(n + 1, 0);
        vector<int> pre(26, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 26; j++) {
                if (pre[j] >= pre[s[i] - 'a']) {
                    f[i] = (f[i] + f[pre[j]]) % P;
                }
            }
            if (!pre[s[i] - 'a']) {
                f[i] = (f[i] + 1) % P;
            }
            pre[s[i] - 'a'] = i;
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            ans = (ans + f[pre[i]]) % P;
        }
        cout << ans << "\n";
    }
    return 0;
}
