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
const int maxn = 40 + 10, mod = 1e9 + 7;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, k;
int p[maxn];
int cnt = 0, tot = 0;
pair<int,int> e[maxn * maxn];
pair<int,int> e1[maxn * maxn];
int ans;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
bool check(){
    int res = 0;
    for(int i = 1;i <= n;i++){fa[i] = i;}
    for(int i = 1;i <= tot;i++){
        int u = e1[i].first, v = e1[i].second;
        if(getf(u) != getf(v)){fa[getf(u)] = getf(v);res++;}
    }
    return res == n - 1;
}
void dfs(int u,int prob){
    if(u == cnt + 1){
        if(check())ans = (ans + prob) % mod;
        return;
    }
    e1[++tot] = e[u];dfs(u + 1,prob * (1 - p[0] + mod) % mod);
    tot--;dfs(u + 1,prob * p[0] % mod);
}
void main(){
    n = read(); k = read();
    for(int i = 0;i <= k;i++)p[i] = read() * qpow(100,mod - 2) % mod;
    for(int i = 1;i <= n;i++)for(int j = i + 1;j <= n;j++)
        e[++cnt] = make_pair(i,j);
    dfs(1,1);
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("mst.in","r",stdin);
    freopen("mst.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}