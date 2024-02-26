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
int qpow(int x,int a){
    int res = 1;x %= mod;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int inv(int x){return qpow(x,mod - 2);}
int n, m, T;
namespace Subtask3{
int A[maxn], B[maxn], C[maxn];
int f[maxn];
int a[maxn], b[maxn];
void solve(){
    f[0] = f[m] = 0;
    a[0] = b[0] = 0;
    a[1] = 1;b[1] = 0;
    for(int i = 1;i < m;i++){
        int fra = inv((m - i) * (m - i) % mod);
        A[i] = (m * m % mod - 2 * i * (m - i) % mod + mod) % mod * fra % mod;
        B[i] = mod - i * i % mod * fra % mod;
        C[i] = mod - m * m % mod * fra % mod;
        a[i + 1] = (A[i] * a[i] % mod + B[i] * a[i - 1] % mod) % mod;
        b[i + 1] = (A[i] * b[i] % mod + B[i] * b[i - 1] % mod + C[i]) % mod;
    }
    f[1] = (mod - b[m]) * inv(a[m]) % mod;
    for(int i = 2;i <= m;i++){f[i] = (a[i] * f[1] % mod + b[i]) % mod;}
    // for(int i = 1;i <= m;i++)printf("i = %lld,f = %lld,a = %lld, b = %lld\n",i,f[i],a[i],b[i]);puts("");
    while(T--){
        int x = read();read();
        printf("%lld\n",f[x]);
    }
}
};
void main(){
    n = read(); m = read(); T = read();
    if(n == 2){Subtask3::solve();}
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