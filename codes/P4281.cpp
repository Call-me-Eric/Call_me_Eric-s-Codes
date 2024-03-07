#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >='0'&&ch <= '9'){x=(x<<3)+(x<<1)+ch-'0';ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m;
int fa[maxn][21], dep[maxn];
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
}e[maxn * 2];
void add(int u,int v){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    head[u] = tot;
}
void dfs(int u,int f){
    fa[u][0] = f; dep[u] = dep[f] + 1; int v = 0;
    for(int i = 1;(1 << i) <= dep[u];i++){
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int i = head[u];i != -1;i = e[i].nextedge){
        v = e[i].topoint;
        if(v == f)continue;
        dfs(v,u);
    }
}
int lca(int u,int v){
    if(dep[u] > dep[v])swap(u, v);
    for(int i = 19;i >= 0;i--){
        if(dep[u] <= dep[v] - (1 << i))v = fa[v][i];
    }
    if(u == v)return u;
    for(int i = 19;i >= 0;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i]; v = fa[v][i];
        }
    }
    return fa[u][0];
}
int ans = 0;
int solve(int u,int v,int w){
    int l[3] = {lca(u,v),lca(v,w),lca(u,w)}, p = 0;
    if(l[0] == l[1]) p = l[2]; if(l[2] == l[1]) p = l[0]; if(l[0] == l[2]) p = l[1];
    ans = dep[u] + dep[v] + dep[w] - dep[l[0]] - dep[l[1]] - dep[l[2]];
    return p;
}
signed main(){
    memset(head,-1,sizeof(head));
    n = read(); m = read();
    int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    dfs(1,0);
    while(m--) printf("%d %d\n",solve(read(),read(),read()),ans);
    return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;

const int MAXN=5*1e5+9;
int n,m,x,y,z,head[MAXN],dep[MAXN],f[MAXN][21],cnt,LCA1,LCA2,LCA3,p;
struct record {
    int u,v;
} edge[MAXN*2];

void add(int x,int y) {
    edge[cnt].u=head[x];
    edge[cnt].v=y;
    head[x]=cnt++;
}
void dfs(int u,int fa) {
    dep[u]=dep[fa]+1,f[u][0]=fa;
    for (int i=1; (1<<i)<=dep[u]; i++) f[u][i]=f[f[u][i-1]][i-1];
    for (int i=head[u]; i!=-1; i=edge[i].u)
        if (edge[i].v!=fa) dfs(edge[i].v,u);
}
int LCA(int x,int y) {
    if(dep[x]>dep[y]) swap(x,y);
    for(int i=19; i>=0; i--)
        if (dep[x]<=dep[y]-(1<<i)) y=f[y][i];
    if (x==y) return x;
    for(int i=19; i>=0; i--)
        if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int main() {
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for (int i=1; i<n; i++) {
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    while (m--) {
        scanf("%d%d%d",&x,&y,&z);
        LCA1=LCA(x,y),LCA2=LCA(y,z),LCA3=LCA(z,x);
        if (LCA1==LCA2) p=LCA3;
        if (LCA1==LCA3) p=LCA2;
        if (LCA2==LCA3) p=LCA1;
        printf("%d %d\n",p,dep[x]+dep[y]+dep[z]-dep[LCA1]-dep[LCA2]-dep[LCA3]);
    }
    return 0;
}*/