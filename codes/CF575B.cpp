#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxk = 1e6 + 10, mod = 1e9 + 7;
int n, k;
int s[maxk];

int head[maxn], tot = 1;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int fa[maxn][31], dep[maxn];
void dfs(int u,int f){
    for(int i = 1;i <= 30;i++)fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = head[u];i;i = e[i].nexte){
        int v=  e[i].to; if(v == f)continue;
        dep[v] = dep[u] + 1;fa[v][0] = u;dfs(v, u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 30;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v])u = fa[u][i];
    }
    if(u == v)return u;
    for(int i = 30;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];v = fa[v][i];
        }
    }
    return fa[u][0];
}
int up[maxn], down[maxn];
int pw[maxk];
int ans = 0;
void dfs1(int u,int f){
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;if(v == f)continue;
        dfs1(v, u);up[u] += up[v]; down[u] += down[v];
        ans = (ans + e[i ^ 1].wei * (pw[up[v]] - 1)) % mod;
        ans = (ans + e[i  ].wei * (pw[down[v]] - 1)) % mod;
    }
}

signed main(){
    n = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v=  read(); w= read();
        add(u, v, 0);add(v, u, w);
    }
    dep[1] = 1;dfs(1, 0);
    k = read(); s[0] = 1;pw[0] = 1;
    for(int i = 1;i <= k;i++){s[i] = read();pw[i] = pw[i - 1] * 2 % mod;}
    for(int i = 1;i <= k;i++){
        int lca = LCA(s[i - 1],s[i]);
        up[s[i - 1]]++; up[lca]--;
        down[s[i]]++;down[lca]--;
    }
    dfs1(1 ,0);
    printf("%lld\n",ans);
    return 0;
}