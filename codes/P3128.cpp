#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e4 + 10, maxm = 1e5 + 10;
int fa[maxn][21], dep[maxn];
int head[maxn], tot;
int cf[maxn], ans[maxn];
struct edge{int topoint, nextedge;edge(int to = 0,int ne = 0):topoint(to),nextedge(ne){}}e[maxm * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
void dfs(int u,int father,int depth){
    dep[u] = depth; fa[u][0] = father;
    for(int i = 1;i <= 20;i++)fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(father == v)continue;
        dfs(v,u,depth + 1);
    }
}
void dfs1(int u){
    ans[u] = cf[u];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u][0])continue;
        dfs1(v);
        ans[u] += ans[v];
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
signed main(){
    n = read(); m = read();
    int u ,v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v);add(v,u);
    }
    dfs(1,0,0);
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        int lca = LCA(u,v);
        cf[u]++; cf[v]++; cf[lca]--;
        cf[fa[lca][0]]--;
    }
    dfs1(1);
    int res = -1;
    for(int i = 1;i <= n;i++){
        res = max(res,ans[i]);
    }
    printf("%d\n",res);
    return 0;
}