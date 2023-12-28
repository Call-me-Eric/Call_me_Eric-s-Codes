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

const int MAXN  = 1e6 + 5;

int n, m, L, ans, ANS;
vector<int> d;

void dfs(int now, int las) {
    int sz = __builtin_popcountll(now);
    if(sz > m) return ;
    if(ans < sz) ans = sz, ANS = now;
    if(ans == m) {
        for(int i = 0; i < n; i++) putchar('0' + ((ANS >> i) & 1));
        exit(0);
    }
    for(int i = las; i < L; i++)
     if(!(now & d[i])) dfs(now | d[i], i + 1);
}

signed main() {
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
    n = read(); m = read();
    if(n == m) {
        for(int i = 1; i <= n; i++) putchar('1');
        return 0;
    }
    if(m <= 1 || n > 36) {
        for(int i = 1; i <= n; i++) putchar('0');
        return 0;
    }
    for(int i = 2; i < n; i++)
     if(n % i == 0) {
        int S = 0;
        for(int p = 0; p < n; p += i) S |= (1ll << p);
        for(int j = 0; j < i; j++) {
            d.push_back(S);
            S = (S >> 1) | ((S & 1) << (n - 1));
        }
     }
    L = (int)(d.size());
    dfs(0, 0);
    for(int i = 0; i < n; i++) putchar('0' + ((ANS >> i) & 1));
    return 0;
}
