#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int res = 0, f = 1; char ch;
    while((ch = getchar()) && (ch < '0' || ch > '9') && ch != '-');
    (ch == '-') ? f = -1 : res = ch - '0';
    while((ch = getchar()) && ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + ch - '0';
    return res * f;
}

inline void print(int x, char ch = '\n') {
    if(x < 0) putchar('-'), x = -x;
    static short prnum[21];
    short prcnt = 0;
    do { prnum[++prcnt] = x % 10; x /= 10; } while(x > 0);
    while(prcnt) putchar(prnum[prcnt--] + '0');
    putchar(ch);
}

const int MAXN  = 705, MOD = 998244353;

int n, m, dat[MAXN][MAXN], a[MAXN][MAXN];

inline int expow(int x, int y) {
    int res = 1;
    while(y) {
        if(y & 1) res = res * x % MOD;
        y >>= 1, x = x * x % MOD;
    }
    return res;
}

void solve() {
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= n + 1; j++)
      a[i][j] = dat[i][j];
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++)
         if(a[j][i]) {
            if(j == i) break;
            for(int k = i; k <= n + 1; k++) swap(a[i][k], a[j][k]);
            break;
         }
        if(!a[i][i]) return puts(a[i][n + 1] ? "No" : "Many"), void();
        for(int j = i + 1; j <= n; j++)
         if(a[j][i]) {
            int v = a[j][i] * expow(a[i][i], MOD - 2) % MOD;
            for(int k = i; k <= n + 1; k++)
             a[j][k] = (a[j][k] - a[i][k] * v) % MOD;
         }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++)
         a[i][n + 1] = (a[i][n + 1] - a[i][j] * a[j][n + 1]) % MOD;
        a[i][n + 1] = (a[i][n + 1] * expow(a[i][i], MOD - 2) % MOD + MOD) % MOD;
    }
    for(int i = 1; i <= n; i++) print(a[i][n + 1], ' ');
    putchar('\n');
}

signed main() {
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    n = read(); m = read();
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= n + 1; j++) dat[i][j] = read();
    solve();
    while(m--) {
        int x = read();
        for(int i = 1; i <= n + 1; i++) dat[x][i] = read();
        solve();
    }
    return 0;
}