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
const int maxn = 1e5 + 10;
int n;
int d[maxn], lca[maxn];
vector<int> edg[maxn];
int fa[21][maxn];
int dep[maxn];
void dfs(int u,int f){
    fa[0][u] = f;dep[u] = dep[f] + 1;
    for(int i = 1;i <= 20;i++)fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(int v : edg[u])if(v != f)dfs(v, u);
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
pair<int,int> ed[maxn];
int val[maxn], tmp[maxn];
void main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        ed[i] = make_pair(u, v);
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 1);
    for(int i = 1;i < n;i++)d[i] = read(),lca[i] = LCA(i,i + 1);
    for(int j = 1;j <= 60;j++){
        for(int i = 1;i <= n;i++)tmp[i] = val[i];int mod = (1ll << j);
        for(int i = 2;i <= n;i++)val[i] = (tmp[lca[i - 1]] * 2ll % mod + d[i - 1] % mod - val[i - 1] % mod + mod) % mod;
    }
    bool flag = true;
    vector<int> ans;
    // for(int i = 1;i <= n;i++)printf("%lld ",val[i]);puts("");
    for(int i = 1;i < n;i++){
        u = ed[i].first, v = ed[i].second;
        if(fa[0][u] == v)swap(u, v);
        ans.push_back(val[v] - val[u]);
        if(val[u] >= val[v] || val[v] - val[u] > 1e12){flag = false;break;}
        if(val[i] + val[i + 1] - 2ll * val[lca[i]] != d[i]){flag = false;break;}
    }
    if(!flag){puts("-1");return;}
    for(int i : ans)printf("%lld\n",i);
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