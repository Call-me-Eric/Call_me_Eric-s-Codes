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
const int maxn = 1e6 + 10, N = 1e15;
int f[maxn], g[maxn];
set<int> s;
int a[maxn], tot, T, mod;
inline int F(int x,int y){return a[x] % y ? 0 : f[lower_bound(a,a + 1 + tot,a[x] / y) - a];}
inline int G(int x,int y){return a[x] % y ? 0 : g[lower_bound(a,a + 1 + tot,a[x] / y) - a];}
void main(){
    f[0] = read(); g[0] = read(); T = read(); mod = read();
    for(int i = 1;i <= 13;i++){
        f[i] = max(i,g[i / 2] + g[i / 3] + g[i / 5] + g[i / 7]);
        g[i] = max(i,f[i / 2] + f[i / 3] + f[i / 5] + f[i / 4]);
    }
    for(int i = 13;i >= 1;i--){
        f[i] -= f[i - 1];g[i] -= g[i - 1];
        f[i] = (f[i] % mod + mod) % mod;
        g[i] = (g[i] % mod + mod) % mod;
    }
    f[0] %= mod;g[0] %= mod;
    for(int i = 1;i <= 13;i++)for(int j = i;j <= N;j *= 2)
    for(int k = j;k <= N;k *= 3)for(int l = k;l <= N;l *= 5)
    for(int p = l;p <= N;p *= 7)s.insert(p);
    for(int i : s)a[++tot] = i;
    for(int i = 14;i <= tot;i++){
        f[i] = (G(i,2) + G(i,3) + G(i,5) + G(i,7)) % mod;
        g[i] = (F(i,2) + F(i,3) + F(i,5) + F(i,4)) % mod;
    }
    for(int i = 1;i <= tot;i++){f[i] = (f[i] + f[i - 1]) % mod;g[i] = (g[i] + g[i - 1]) % mod;}
    while(T--){int pos = upper_bound(a,a + 1 + tot,read()) - a - 1;printf("%lld %lld\n",f[pos],g[pos]);}
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