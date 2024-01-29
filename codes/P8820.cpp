#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, Q, k;
int head[maxn], tot;
int cost[maxn], mn[maxn];
struct edge{int topoint, nextedge;edge(int t = 0,int n = 0):topoint(t),nextedge(n){}}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dis[maxn][21][3][3];
int fa[maxn][21], dep[maxn];
void dfs(int u,int f){
    dep[u] = dep[f] + 1; fa[u][0] = f;
    for(int i = 1;i <= 20;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    if(k == 1){dis[u][0][0][0] = cost[f];}
    else if(k == 2){
        dis[u][0][0][0] = dis[u][0][1][0] = cost[f];
        dis[u][0][0][1] = 0;
    }
    else if(k == 3){
        dis[u][0][0][0] = dis[u][0][1][0] = dis[u][0][2][0] = cost[f];
        dis[u][0][0][1] = dis[u][0][1][2] = 0;
        dis[u][0][2][2] = mn[u];
    }
    for(int i = 1;i <= 20;i++)
    for(int x = 0;x < 3;x++)
    for(int y = 0;y < 3;y++)
        for(int z = 0;z < 3;z++)
            dis[u][i][x][z] = min(dis[u][i][x][z],dis[u][i - 1][x][y] + dis[fa[u][i - 1]][i - 1][y][z]);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v != f) dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--)if(dep[fa[u][i]] >= dep[v])u = fa[u][i];
    if(u == v)return u;
    for(int i = 20;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
vector<int> calc(int u,int l){
    vector<int> res(3,cost[u]);
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] < dep[l])continue;
        vector<int> tmp = res;
        fill(res.begin(),res.end(),0x3f3f3f3f3f3f);
        for(int x = 0;x < 3;x++)
            for(int y = 0;y < 3;y++)
                res[y] = min(res[y],tmp[x] + dis[u][i][x][y]);
        u = fa[u][i];
    }
    return res;
}
int getans(int u,int v){
    int lca = LCA(u,v);
    vector<int> F = calc(u,lca), G = calc(v,lca);
    int res = F[0] + G[0] - cost[lca];
    for(int i = 0;i < k;i++)
        for(int j = 0;j < k;j++)
            res = min(res,F[i] + G[j] + ((i + j > k) * mn[lca]));
    return res;
}
signed main(){
    n = read(); Q = read(); k = read(); int u, v;
    for(int i = 1;i <= n;i++)mn[i] = cost[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
        mn[u] = min(mn[u],cost[v]);
        mn[v] = min(mn[v],cost[u]);
    }
    memset(dis,1,sizeof(dis));
    dfs(1,0);
    for(int i = 1;i <= Q;i++){
        u = read(); v = read();
        printf("%lld\n",getans(u,v));
    }
    return 0;
}