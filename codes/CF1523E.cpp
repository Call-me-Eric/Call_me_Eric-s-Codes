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
const int maxn = 1e5 + 10,mod = 1e9 + 7;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, k;
int pw[maxn], invpw[maxn];
int C(int n,int m){return n < m ? 0 : pw[n] * invpw[n - m] % mod * invpw[m] % mod;}
void solve(){
    n = read(); k = read();pw[0] = invpw[0] = 1;
    for(int i = 1;i <= n;i++)pw[i] = pw[i - 1] * i % mod;
    invpw[n] = qpow(pw[n],mod - 2);
    for(int i = n - 1;i;i--)invpw[i] = invpw[i + 1] * (i + 1) % mod;
    int ans = 1;
    for(int i = 1;i < n;i++)
        ans = (ans + C(n - (i - 1) * (k - 1),i) * qpow(C(n,i), mod - 2) % mod) % mod;
    printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
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