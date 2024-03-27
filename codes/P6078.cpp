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
const int maxn = 20, mod = 2004;
int n, a, b, fac = 1, ans = 0;
int m[maxn];
int C(int n,int m){
    int modd = mod * fac;
    int res = 1;
    for(int i = n - m + 1;i <= n;i++)res = res * i % modd;
    return (res / fac) % mod;
}
void dfs(int u,int f,int k,int lim){
    if(k > lim)return;
    if(u == n + 1){ans = (ans + f * C(n + lim - k,n) % mod + mod) % mod;return;}
    dfs(u + 1,f,k,lim);
    dfs(u + 1,-f,k + m[u] + 1,lim);
}
int solve(int x){
    ans = 0;dfs(1,1,0,x);
    return (ans % mod + mod) % mod;
}
void main(){
    n = read(); a = read(); b = read();
    for(int i = 1;i <= n;i++){m[i] = read();fac = fac * i;}
    printf("%lld\n",(solve(b) - solve(a - 1) + mod) % mod);
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