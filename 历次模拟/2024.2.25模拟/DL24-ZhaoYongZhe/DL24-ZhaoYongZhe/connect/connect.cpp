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
namespace Subtask1{
    int fa[maxn],siz[maxn];
    int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
    void main(){
        for(int i = 1;i <= n;i++)fa[i] = i;
        for(int i = 1;i <= n;i++)
            if(a[i] == 1)for(int v : edg[i])
                if(a[v] == 1)fa[getf(i)] = getf(v);
        for(int i = 1;i <= n;i++)siz[getf(i)] += (a[i] == 1);
        int ans = 0;
        for(int i = 1;i <= n;i++){ans = (ans - 1 + qpow(2,siz[i]) + mod) % mod;}
        printf("%lld\n",ans);
    }
};
void main(){
    int u, v;
    n = read(); X = read(); Y = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    if(Y == 1){Subtask1::main();}
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