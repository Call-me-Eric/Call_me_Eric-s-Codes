#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f= -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m, point[maxn];

vector<int> edg[maxn];

int dep[maxn], fa[maxn][31];
void dfs(int u,int f){
    dep[u] = dep[f] + 1;fa[u][0] = f;
    for(int i = 1;i <= 30;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int v : edg[u]){if(v != f){dfs(v, u);}}
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 30;i + 1;i--)
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if(u == v)return u;
    for(int i = 30;i + 1;i--)
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

bool col[maxn];
void dfs1(int u, int top){if(col[u])return;col[u] = 1;if(u == top)return;dfs1(fa[u][0], top);}

vector<int> edg1[maxn];
void dfs2(int u,int f){
    dep[u] = dep[f] + 1;
    for(int v : edg1[u]){if(v != f)dfs2(v, u);}
}

signed main(){
    n = read(); m = read(); int u, v;
    for(int i =1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v); edg[v].push_back(u);
    }
    for(int i = 1;i <= m;i++)point[i] = read();
    if(m == 1){printf("%d\n",point[1]);puts("0");return 0;}
    
    dfs(1, 0); int lca = LCA(point[1],point[2]);
    for(int i = 3;i <= m;i++){lca = LCA(lca,point[i]);}
    for(int i = 1;i <= m;i++){dfs1(point[i], lca);}
    int tot = 0, root = lca, l = lca, r = lca;
    // for(int i = 1;i <= n;i++){printf("col[%d] = %d\n",i,col[i]);}

    for(int i = 1;i <= n;i++)if(col[i]){tot++;for(int j : edg[i]){if(col[j])edg1[i].push_back(j);}}
    memset(dep,0,sizeof(dep));dep[root] = 0;dfs2(root,root);
    for(int i = 1;i <= n;i++){if(col[i] && dep[i] > dep[root])root = i;}
    memset(dep,0,sizeof(dep));l = root;dep[root] = 0;dfs2(root,root);
    
    int res = 0; for(int i = 1;i <= n;i++){if(col[i] && (dep[i] > res)){r = i;res = dep[r];}}
    // printf("tot=%d,res=%d\n",tot,res);
    // for(int i = 1;i <= n;i++){printf("dep[%d] = %d\n",i,dep[i]);}
    printf("%d\n%d\n",min(l,r),(tot - 1) * 2 - res + 1);
    return 0;
}