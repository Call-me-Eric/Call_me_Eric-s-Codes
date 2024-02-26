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
const int maxn = 1e5 + 10, mod = 998244353;
pair<int,int> f[maxn];
int dp[maxn];
int n, m, T;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void main(){
    n = read(); m = read(); T = read();
    int invn = qpow(n,mod - 2), invm = qpow(m,mod - 2);
    int inv = qpow((n - 1) * m % mod,mod - 2),num = (n - 1) * m % mod;
    for(int i = 0;i < m;i++){
        int t0 = i * invm % mod, t1 = (m - i) * invm % mod;
        int t2 = (m - i) * inv % mod, t3 = (num - (m - i) + mod) * inv % mod;
        int a = t0 * t3 % mod, b = (t0 * t2 % mod + t1 * t3 % mod) % mod;
        int c = t1 * t2 % mod, d = 1;
        b = (1 - b + mod) % mod;
        if(i){
            b = (b - a * f[i - 1].first % mod + mod) % mod;
            d = (d + a * f[i - 1].second % mod + mod) % mod;
        }
        int tmp = qpow(b,mod - 2);
        f[i] = make_pair(c * tmp % mod,d * tmp % mod);
    }
    for(int i = m - 1;i + 1;i--)
        dp[i] = (dp[i + 1] * f[i].first % mod + f[i].second) % mod;
    while(T--){
        int ans = 0;
        for(int i = 1;i <= n;i++)ans = (ans + dp[read()]) % mod;
        ans = (ans - dp[0] * (n - 1) % mod + mod) % mod * invn % mod;
        printf("%lld\n",ans);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("cards.in","r",stdin);
    freopen("cards.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}