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
const int maxn = 1e3 + 10, mod = 1e9 + 7;
int n, X, Y;
int a[maxn];
vector<int> edg[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
map<pair<int,int>,int> f[maxn];
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
inline int lcm(int x,int y){return x / gcd(x, y) * y;}
void dfs(int u,int fa){
    f[u][make_pair(a[u],a[u])] = 1;
    for(int v : edg[u]){
        if(a[v] <= Y && v != fa){
            dfs(v, u);auto tmp = f[u];
            for(auto [pi0,f0] : tmp)
                for(auto [pi1,f1] : f[v]){
                    auto ttt = make_pair(gcd(pi0.first,pi1.first),lcm(pi0.second,pi1.second));
                    f[u][ttt] = (f[u][ttt] + f0 * f1 % mod) % mod;
                }
        }
    }
}
void main(){
    int u, v;
    n = read(); X = read(); Y = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1 ,0);int ans = 0;
    for(int i = 1;i <= n;i++)ans = (ans + f[i][make_pair(X,Y)]) % mod;
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("connect.in","r",stdin);
    freopen("connect.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}