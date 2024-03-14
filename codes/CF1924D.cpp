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
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int pw[maxn], invpw[maxn];
int C(int n,int m){return pw[n] * invpw[m] % mod * invpw[n - m] % mod;}
int n, m, k;
void main(){
    pw[0] = invpw[0] = 1;
    for(int i = 1;i < maxn;i++)pw[i] = pw[i - 1] * i % mod;
    invpw[maxn - 1] = qpow(pw[maxn - 1],mod - 2);
    for(int i = maxn - 2;i;i--)invpw[i] = invpw[i + 1] * (i + 1) % mod;
    int T = read();
    while(T--){
        n = read(); m = read(); k = read();
        if(k > min(n, m))puts("0");
        else printf("%lld\n",(C(n + m,k) - C(n + m,k - 1) + mod) % mod);
    }
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