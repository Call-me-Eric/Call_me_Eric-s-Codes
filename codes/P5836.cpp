#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int fa[maxn][21], dep[maxn];
bool dis[maxn][21][3];
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int t = 0,int n = 0):topoint(t),nextedge(n){}
}e[maxn * 2];
int val[maxn];
int n, m;char ch[maxn];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
void dfs(int u,int f){
    dep[u] = dep[f] + 1; fa[u][0] = f;
    dis[u][0][1] = val[u] == 1 || val[f] == 1;
    dis[u][0][2] = val[u] == 2 || val[f] == 2;
    for(int i = 1;i <= 20;i++){
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        dis[u][i][1] = dis[u][i - 1][1] | dis[fa[u][i - 1]][i - 1][1];
        dis[u][i][2] = dis[u][i - 1][2] | dis[fa[u][i - 1]][i - 1][2];
    }
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        dfs(v,u);
    }
}
bool getans(int u,int v,int opt){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v]){
            if(dis[u][i][opt])return true;
            u = fa[u][i];
        }
    }
    if(u == v)return val[u] == opt;
    for(int i = 20;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            if(dis[u][i][opt] || dis[v][i][opt])return true;
            u = fa[u][i]; v = fa[v][i];
        } 
    }
    return dis[u][0][opt] || dis[v][0][opt];
}
signed main(){
    scanf("%d%d",&n, &m);
    scanf("%s",ch + 1); int u, v; 
    for(int i = 1;i <= n;i++)val[i] = ch[i] - 'G' + 1;
    for(int i = 1;i < n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    memset(ch,0,sizeof(ch));
    dfs(1,0);char opt;
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&u,&v);opt = ' ';
        while(opt != 'G' && opt != 'H'){opt = getchar();}
        putchar(getans(u,v,opt - 'G' + 1) ? '1' : '0');
    }
    return 0;
}