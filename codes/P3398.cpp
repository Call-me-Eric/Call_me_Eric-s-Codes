#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
}e[maxn * 2];
int n, q;
int fa[maxn][21], dep[maxn];
void add(int u,int v){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    head[u] = tot;
}
void dfs(int u,int f){
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        dfs(v,u);
    }
    return;
}
int lca(int x,int y){
    if(dep[x] < dep[y])swap(x, y);
    for(int i = 20;i >= 0;i--){
        if(dep[fa[x][i]] >= dep[y])x = fa[x][i];
    }
    if(x == y)return x;
    for(int i = 20;i >= 0;i--){
        if(fa[x][i] != fa[y][i]){
            x = fa[x][i]; y = fa[y][i];
        }
    }
    return fa[x][0];
}
bool check(int a,int b,int c,int d){
    int lca1 = lca(a, b), lca2 = lca(c, d);
    int st = max(max(dep[lca(a,c)],dep[lca(b, d)]),max(dep[lca(a,d)],dep[lca(b,c)]));
    return st >= dep[lca1] && st >= dep[lca2];
}
int main(){
    int u, v, a, b, c, d;
    n = read(); q = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(v, u);
        add(u, v);
    }
    dep[1] = -1;
    dfs(1, 1);
    for(int i = 0;i <= 20;i++){
        fa[1][i] = 1;
    }
    for(int k = 1;k <= 20;k++){
        for(int i = 1;i <= n;i++){
            fa[i][k] = fa[fa[i][k - 1]][k - 1];
        }
    }
    for(int i = 1;i <= q;i++){
        a = read(); b = read(); c = read(); d = read();
        puts(check(a,b,c,d)?"Y":"N");
    }
    return 0;
}