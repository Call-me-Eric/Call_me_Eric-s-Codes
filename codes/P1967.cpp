#include<bits/stdc++.h>
using namespace std;
int n, m, k;
const int maxn = 1e5 * 2;
int fa[maxn];
bool book[maxn];
int depth[maxn];
int lca[maxn][22];
int w[maxn][22];
struct node{
    int nextedge,topoint,weight;
}edge[maxn];
struct node1{
    int u, v ,w;
}e[maxn];
int head[maxn], tot;
void add(int u,int v,int w){
    edge[++tot].topoint = v;
    edge[tot].weight = w;
    edge[tot].nextedge = head[u];
    head[u] = tot;
}
int getf(int x){
    if(fa[x] != x)fa[x] = getf(fa[x]);
    return fa[x];
}
struct cmp{
    bool operator ()(node1 a,node1 b){
        return a.w > b.w;
    }
};
void dfs(int x,int fa,int dep){
    depth[x] = dep;
    book[x] = 1;
    for(int i = head[x];i;i = edge[i].nextedge){
        int j = edge[i].topoint;
        if(j != fa && !book[j]){
            book[j] = 1;
            lca[j][0] = x;
            w[j][0] = edge[i].weight;
            dfs(j,x,dep + 1);
        }
    }
    return;
}
int LCA(int u,int v){
    if(getf(u) != getf(v))return -1;
    int ans = 0x3f3f3f3f;
    if(depth[u] > depth[v])swap(u,v);
    for(int i = 20;i >= 0;i--){
        if(depth[lca[v][i]] >= depth[u]){
            ans = min(ans, w[v][i]);
            v = lca[v][i];
        }
    }
    if(u == v)return ans;
    for(int i = 20;i >= 0;i--){
        if(lca[v][i] != lca[u][i]){
            ans = min(ans,min(w[v][i],w[u][i]));
            u = lca[u][i];
            v = lca[v][i];
        }
    }
    ans = min(ans,min(w[u][0],w[v][0]));
    return ans;
}
int main(){
    int u, v, ww;
    scanf("%d%d",&n,&m);
    //TODO Init

    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&u,&v,&ww);
        e[i].u = u;e[i].v = v;e[i].w = ww;
    }
    
    //FIXME Init end
    //TODO Kruskal

    sort(e + 1,e + 1 + m,cmp());
    for(int i = 1;i <= m;i++){
        if(getf(e[i].u) != getf(e[i].v)){
            fa[getf(e[i].u)] = getf(e[i].v);
            add(e[i].u,e[i].v,e[i].w);
            add(e[i].v,e[i].u,e[i].w);
        }
    }
    
    //FIXME Kruskal end
    //TODO LCA Init
    for(int i = 1;i <= n;i++){
        if(!book[i]){
            book[i] = 1;
            depth[i] = 1;
            dfs(1,0,1);
            lca[i][0] = i;
            w[i][0] = 0x3f3f3f3f;
        }
    }
    for(int i = 1;i <= 20;i++){
        for(int j = 1;j <= n;j++){
            lca[j][i] = lca[lca[j][i - 1]][i - 1];
            w[j][i] = min(w[j][i - 1],w[lca[j][i - 1]][i - 1]);
        }
    }
    //FIXME LCA end
    scanf("%d",&k);
    for(int i = 1;i <= k;i++){
        scanf("%d%d",&u,&v);
        printf("%d\n",LCA(u,v));
    }
    return 0;
}