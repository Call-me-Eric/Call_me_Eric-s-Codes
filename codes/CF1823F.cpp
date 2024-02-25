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
const int maxn = 2e5 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
inline int inv(int x){return qpow(x, mod - 2);}
inline int frac(int x,int y){return x * inv(y) % mod;}
int n, S, T;
vector<int> edg[maxn];

int deg[maxn];
int A[maxn], B[maxn];
int f[maxn];
void dfs1(int u,int fa){
    int y = 1, x = (u == S);
    for(int v : edg[u]){
        if(v != fa){
            dfs1(v, u);
            y = (y - frac(A[v],deg[v]) + mod) % mod;
            x = (x + frac(B[v],deg[v])) % mod;
        }
    }
    A[u] = frac(1,deg[fa] * y % mod);
    B[u] = frac(x, y);
    if(fa == T)A[u] = 0;
}
void dfs2(int u,int fa){
    for(int v : edg[u]){
        if(v != fa){
            f[v] = (A[v] * f[u] % mod + B[v]) % mod;
            dfs2(v, u);
        }
    }
}
void main(){
    n = read(); S = read(); T = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].emplace_back(v);edg[v].emplace_back(u);
        deg[u]++; deg[v]++;
    }
    dfs1(T,0);f[T] = 1;dfs2(T,0);
    for(int i = 1;i <= n;i++)printf("%lld ",f[i]);
    puts("");
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