#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 3e5 + 10;

int fa[maxn][21], dep[maxn];
int head[maxn], tot;
int low[maxn];
struct edge{int frompoint, topoint, nextedge;edge(int fr = 0,int to = 0,int ne = 0):frompoint(fr),topoint(to),nextedge(ne){}}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(u,v,head[u]);head[u] = tot;}
void dfs(int u){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u][0])continue;
        fa[v][0] = u; dep[v] = dep[u] + 1;
        for(int j = 1;j <= low[dep[v]];j++)fa[v][j] = fa[fa[v][j - 1]][j - 1];
        dfs(v);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    while(dep[u] > dep[v]) u = fa[u][low[dep[u] - dep[v]]];
    if(u == v)return u;
    for(int i = low[dep[u]];i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

struct node{int d, tmp;node(int a = 0,int b = 0):d(a),tmp(b){}};
vector<node> tmp1[maxn],tmp2[maxn];
int book1[maxn], book2[maxn << 1];//可能下行处理时出现负数，于是加maxn
int w[maxn], s[maxn], t[maxn], lca[maxn];
int ans[maxn];
void dfs1(int u){
    int last = book1[dep[u] + w[u]];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u][0])continue;
        dfs1(v);
    }
    for(int i = 0,len = tmp1[u].size();i < len;i++){
        book1[tmp1[u][i].d] += tmp1[u][i].tmp;
    }
    int now = book1[dep[u] + w[u]];
    ans[u] += now - last;
}
void dfs2(int u){
    int last = book2[w[u] - dep[u] + maxn];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u][0])continue;
        dfs2(v);
    }
    for(int i = 0,len = tmp2[u].size();i < len;i++){
        book2[tmp2[u][i].d + maxn] += tmp2[u][i].tmp;
    }
    int now = book2[w[u] - dep[u] + maxn];
    ans[u] += now - last;
}
signed main(){
    int u, v;
    n = read(); m = read();
    low[1] = 0;
    for(int i = 2;i <= n;i++)low[i] = low[i >> 1] + 1;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v); add(v,u);
    }
    dfs(1);
    for(int i = 1;i <= n;i++)w[i] = read();
    for(int i = 1;i <= m;i++){s[i] = read();t[i] = read();}
    //处理上行边
    for(int i = 1;i <= m;i++){
        lca[i] = LCA(s[i],t[i]);
        tmp1[s[i]].push_back(node(dep[s[i]],1));
        tmp1[lca[i]].push_back(node(dep[s[i]],-1));
    }
    dfs1(1);
    //处理下行边
    for(int i = 1;i <= m;i++){
        int dist = dep[s[i]] + dep[t[i]] - 2 * dep[lca[i]];
        tmp2[t[i]].push_back(node(dist - dep[t[i]],1));
        if(fa[lca[i]][0]) tmp2[fa[lca[i]][0]].push_back(node(dist - dep[t[i]],-1));
    }
    dfs2(1);
    printf("%d",ans[1]);
    for(int i = 2;i <= n;i++)printf(" %d",ans[i]);
    puts("");
    return 0;
}