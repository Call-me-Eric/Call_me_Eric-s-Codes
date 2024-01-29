#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int n, q;
int dep[maxn];
long long dis[maxn];
int f[maxn][30];
struct Edge{
    int to,weight;
};
vector<Edge> e[maxn];
void dfs(int u,int fa){
    f[u][0] = fa;
    for(int i = 1;i <= 20;i++){
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for(int i = e[u].size() - 1;i >= 0;i--){
        int v = e[u][i].to;
        int w = e[u][i].weight;
        if(v == fa)continue;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + w;
        dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    int k = dep[u] - dep[v];
    for(int i = 20;i >= 0;i--){
        if((k >> i) & 1){
            u = f[u][i];
        }
    }
    if(u == v)return u;
    for(int i = 20;i >= 0;i--){
        if(f[u][i] != f[v][i]){
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
int main(){
    scanf("%d%d",&n,&q);
    int u, v, w;
    for(int i = 1;i < n;i++){
        scanf("%d%d%d",&u,&v,&w);
        e[u].push_back(Edge{v,w});
        e[v].push_back(Edge{u,w});
    }
    dep[1] = 0;
    dis[1] = 0;
    dfs(1,0);
    for(int i = 1;i <= q;i++){
        scanf("%d%d",&u,&v);
        printf("%d\n",dis[u] - 2 * dis[LCA(u,v)] + dis[v]);
    }
    return 0;
}