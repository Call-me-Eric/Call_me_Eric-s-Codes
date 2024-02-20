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
const int maxn = 1e4 + 10;
bitset<maxn> e[maxn];
int n, m, q;
bool vis[maxn * 2];
void dfs(int u,int opt){
    vis[u + opt * n] = 1;
    for(int v = 1,mx = opt ? n : m;v <= mx;v++){
        if(!vis[v + (!opt) * n]){
            if(opt){if(!e[v][u]){dfs(v,!opt);}}
            else{if(e[u][v])dfs(v,!opt);}
        }
    }
}
void main(){
    auto stclock = clock();
    n = read(); m = read(); q = read();int l, u, r, d;
    for(int i = 1;i <= q;i++){
        l = read(), u = read(), r = read(), d = read();
        e[l][u] = !e[l][u];e[l][d + 1] = !e[l][d + 1];
        e[r + 1][u] = !e[r + 1][u];e[r + 1][d + 1] = !e[r + 1][d + 1];
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            e[i][j] = e[i][j] ^ e[i - 1][j - 1] ^ e[i - 1][j] ^ e[i][j - 1];
        }
    }
    for(int i = 1;i <= n;i++){
        fill(vis + 1,vis + 1 + n + m,0);dfs(i,0);
        int cnt = 0;
        for(int j = 1;j <= n + m;j++)cnt += vis[j];
        printf("%d ",cnt);
    }
    // cerr << (clock() - stclock) * 1.0 / CLOCKS_PER_SEC << " SEC COST.\n";
    for(int i = 1;i <= m;i++){
        fill(vis + 1,vis + 1 + n + m,0);dfs(i,1);
        int cnt = 0;
        for(int j = 1;j <= n + m;j++)cnt += vis[j];
        printf("%d ",cnt);
    }
    puts("");
    return;
}
};
bool edmemory;
signed main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
3 3 2
1 1 2 2
2 2 3 3
*/