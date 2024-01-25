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
int pw[maxn], invpw[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        a >>= 1;x = x * x % mod;
    }
    return res;
}
int C(int n,int m){return pw[n] * invpw[m] % mod * invpw[n - m] % mod;}
int f[maxn], g[maxn], n, m;
void main(){
    pw[0] = invpw[0] = 1;for(int i = 1;i < maxn;i++)pw[i] = pw[i - 1] * i % mod;
    invpw[maxn - 1] = qpow(pw[maxn - 1], mod - 2);
    for(int i = maxn - 2;i;i--){invpw[i] = (i + 1) * invpw[i + 1] % mod;}
    n = read();m = (n + 1) / 2; int sum = 0;
    for(int i = n;i;i--){
        f[i] = pw[n - i] * pw[i - 1] % mod * C(n - m,i - 1) % mod;
        g[i] = (f[i] - sum * qpow(i,mod - 2) % mod + mod) % mod;sum = (sum + g[i]) % mod;
    }
    for(int i = 1;i <= n;i++)printf("%lld ",g[i]);puts("");
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