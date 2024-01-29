#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <vector>
using namespace std;

int main() {
    static const int tot = 23;
    static const int x[tot] = { 2, 3, 5, 7, 11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649, 666649, 946669 };
    static const int maxl = 100010, maxN = 20000, sigma_size = 10;
    static const long long mod = 998244353;
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    static int S[tot][10], len[tot];
    for (int p = 0; p < tot; p++) {
        int tp = 0, tmp = x[p];
        while (tmp) S[p][tp++] = tmp % 10, tmp /= 10;
        reverse(S[p], S[p] + tp), len[p] = tp;
    }
    static int trans[maxN][sigma_size], cnt;
    function<int(const vector<int>&)> dfs = [&dfs](const vector<int>& L) {
        static map<vector<int>, int> mp;
        if (mp.count(L)) return mp[L];
        int u = mp[L] = ++cnt;
        for (int i = 0; i < sigma_size; i++) {
            vector<int> nxt(tot);
            bool flag = true;
            for (int p = 0; p < tot; p++) {
                nxt[p] = L[p] + (S[p][L[p]] == i);
                if (nxt[p] == len[p]) {
                    flag = false;
                    break;
                }
            }
            if (flag) trans[u][i] = dfs(nxt);
        }
        return u;
    };
    dfs(vector<int>(tot, 0));
    int t;
    scanf("%d", &t);
    auto solve = [](const char* n) {
        int len = strlen(n);
        static long long dp[2][2][maxN];
        int cur = 0;
        memset(dp[cur], 0, sizeof(dp[cur])), dp[cur][1][1] = 1;
        for (int i = 0; i < len; i++) {
            cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur]));
            for (int f = 0; f <= 1; f++)
                for (int u = 1; u <= cnt; u++)
                    for (int d = 0; d <= (f ? n[i] - '0' : sigma_size - 1); d++)
                        dp[cur][f && d == n[i] - '0'][trans[u][d]] += dp[cur ^ 1][f][u];
            for (int f = 0; f <= 1; f++)
                for (int u = 1; u <= cnt; u++)
                    dp[cur][f][u] %= mod;
        }
        long long ret = 0;
        for (int i = 1; i <= cnt; i++) ret += dp[cur][0][i] + dp[cur][1][i];
        return ret % mod;
    };
    while (t--) {
        static char l[maxl], r[maxl];
        scanf("%s", l), scanf("%s", r);
        int i = 0;
        while (l[i] == '0') l[i++] = '9';
        l[i]--;
        printf("%lld\n", (solve(r) - solve(l) + mod) % mod);
    }
    return 0;
}
