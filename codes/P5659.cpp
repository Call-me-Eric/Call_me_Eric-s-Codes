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
const int maxn = 2e3 + 10;

int n;
vector<int> edg[maxn];
int p[maxn];
int d[maxn], d1[maxn], d2[maxn];
int from[maxn], to[maxn], fa[maxn];
int edge[maxn][maxn];
int ed[maxn][maxn],st[maxn][maxn];
bool book[maxn];
void dfs(int u,int rt){
    for(int v : edg[u])if(v != fa[u]){
        fa[v] = u; book[v] = 1;
        if(u != rt){
            if(edge[fa[u]][u] == fa[u] || edge[u][v] == u){book[v] = false;}
            if(edge[fa[u]][u] == 0 || edge[u][v] == 0){book[v] = false;}
            if(ed[u][v] == from[u] && st[u][fa[u]] == to[u] && d1[u] + d2[u] + d[u] * 2 - 2 > 0){book[v] = false;}
            if(ed[u][v] == fa[u]){book[v] = false;}
        }
        else{
            if(edge[u][v] == u){book[v] = false;}
            if(edge[u][v] == 0){book[v] = false;}
            if(from[u] && ed[u][v] == from[u] && d[u] + d1[u] + d2[u] - 1 != 0){book[v] = false;}
        }
        book[v] &= book[u]; dfs(v,rt);
    }
    if(u == rt)book[u] = 0;
    else{
        if(from[u])book[u] = 0;
        if(to[u] && ed[u][to[u]] == fa[u] && d[u] + d1[u] + d2[u] - 1 != 0)book[u] = 0;
    }
}
void solve(){
    n = read();for(int i = 1;i <= n;i++){p[i] = read();edg[i].clear();from[i] = to[i] = d[i] = d1[i] = d2[i] = 0;}

    for(int i = 1;i < n;i++){
        int u = read(), v=  read();
        edg[u].push_back(v);edg[v].push_back(u);
        d[u]++;d[v]++;edge[u][v] = edge[v][u] = -1;
        ed[u][v] = st[u][v] = v;ed[v][u] = st[v][u] = u;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++)book[j] = 0,fa[j] = 0;
        book[p[i]] = 1; dfs(p[i],p[i]);
        int v = 0;
        for(int j = 1;j <= n;j++)if(book[j]){v = j;break;}
        printf("%d ",v);
        from[v] = fa[v];
        while(fa[v] != p[i]){
            if(edge[fa[v]][v] == -1){
                edge[fa[v]][v] = edge[v][fa[v]] = fa[v];
                d[v]--;d2[v]++;
                d[fa[v]]--;d1[fa[v]]++;
            }
            else{
                edge[fa[v]][v] = edge[v][fa[v]] = 0;
                d1[v]--;d2[fa[v]]--;
            }
            int t = v;v = fa[v];
            st[v][ed[v][t]] = st[v][fa[v]];
            ed[v][st[v][fa[v]]] = ed[v][t];
        }
        if(edge[fa[v]][v] == -1){
            edge[fa[v]][v] = edge[v][fa[v]] = fa[v];
            d[v]--;d2[v]++;
            d[fa[v]]--;d1[fa[v]]++;
        }
        else{
            edge[fa[v]][v] = edge[v][fa[v]] = 0;
            d1[v]--;d2[fa[v]]--;
        }
        to[p[i]] = v;
    }
    puts("");
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