#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e6 + 10, mod = 1e9 + 7;
int inv[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;a >>= 1;
    }
    return res;
}
int n, m, S;
void main(){
    inv[1] = 1;
    for(int i = 2;i < maxn;i++){inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;}
    auto solve = [](){
        n = read(); m = read(); S = read() - 1;
        if(n * m <= S){puts("0");return;}
        int ans = 1;
        for(int i = 1;i < n;i++){
            int j = min(S / i,m);if(j == m)continue;
            ans += inv[i + j];if(ans >= mod)ans -= mod;
        }
        for(int i = 1;i < m;i++){
            int j = min(S / i,n);if(j == n)continue;
            ans += inv[i + j];if(ans >= mod)ans -= mod;
        }
        printf("%lld\n",ans);
        return;
    };
    int T = read();while(T--)solve();
    return;
}
};
bool edmemory;
signed main(){
    // freopen("tmp.in","r",stdin);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}