#include<bits/stdc++.h>
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

const int MAXN = 1e5 + 5, MOD = 998244353;

int ban[] = {11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649, 666649, 946669, 60000049, 66000049, 66600049};

char s[MAXN];
int T;
vector<int> S;

inline bool chklcs(int num) {
    for(int y : ban) {
        int x = num;
        if(y > x) break;
        while(x && y) {
            if(x % 10 == y % 10) y /= 10;
            x /= 10;
        }
        if(!y) return true;
    }
    return false;
}

void dfs(int now, int num) {
    if(num && chklcs(num)) return ;
    if(num) S.push_back(num);
    if(now >= 10) return ;
    if(num) dfs(now + 1, num * 10);
    for(int v : {1, 4, 6, 8, 9})
     dfs(now + 1, num * 10 + v);
}

void solve() {
    int l, r;
    l = read(); r = read();
    auto fir = lower_bound(S.begin(), S.end(), l), sec = upper_bound(S.begin(), S.end(), r);
    print(sec - fir);
}

int main() {
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    dfs(1, 0);
    sort(S.begin(), S.end());
    T = read();
    while(T--) solve();
    return 0;
}