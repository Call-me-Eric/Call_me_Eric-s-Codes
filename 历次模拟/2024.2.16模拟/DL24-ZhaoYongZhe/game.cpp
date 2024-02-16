#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, c[maxn];
int fr[maxn], to[maxn];
vector<int> edg[maxn];
bool f[maxn];
void main(){
    n = read();int u, v;
    for(int i = 1;i <= n;i++)c[i] = (read() & 1);
    for(int i = 1;i < n;i++){
        u = read(), v = read();
        if(u < v) swap(u, v);
        fr[i] = u;to[i] = v;
    }
    int ans = 0;
    for(int sta = 1;sta < (1 << (n - 1));sta++){
        for(int i = 1;i <= n;i++){edg[i].clear();f[i] = 0;}
        for(int i = 1;i < n;i++)if((1 << (i - 1)) & sta){edg[fr[i]].push_back(to[i]);}
        for(int i = n;i;i--)
            if(!f[i])for(int v : edg[i])f[v] = 1;
        int x = 0;
        for(int i = 1;i <= n;i++)x ^= (c[i] && f[i]);
        ans += x;
    }
    printf("%d\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}