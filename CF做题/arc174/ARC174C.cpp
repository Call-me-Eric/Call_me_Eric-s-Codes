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
const int maxn = 1e6 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, f[maxn], g[maxn];
void main(){
    n = read();
    f[0] = 0;g[0] = 0;int invn = qpow(n,mod - 2);
    for(int i = 1;i <= n;i++){
        int fac = i * invn % mod;fac = fac * fac % mod;
        f[i] = (f[i - 1] * (fac * qpow(fac - 1 + mod,mod - 2) % mod) % mod * i % mod * invn % mod) + 1;
        g[i] = (g[i - 1] * (fac * qpow(fac - 1 + mod,mod - 2) % mod) % mod * fac % mod) + 1;
    }
    printf("%lld %lld\n",f[n],g[n]);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}