#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 4e4 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
}e[maxn * 2];
void add(int u,int v){e[++tot] = {v,head[u]};head[u] = tot;}
int fa[maxn][21];
int dep[maxn];
void dfs(int u,int fat){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fat)continue;
        fa[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v,u);
    }
}
int LCA(int u,int v){
    bool flag = false;
    if(dep[u] > dep[v]){flag = true;swap(u,v);}
    for(int i = 20;i >= 0;i--){
        if(dep[u] <= dep[fa[v][i]]){
            v = fa[v][i];
        }
    }
    if(u == v)return 1 + flag;
    else return 0;
}
signed main(){
    n = read();
    int root = 0, x, y, maxx = -1;
    for(int i = 1;i <= n;i++){
        x  =read(); y = read();
        maxx = max(maxx,max(x,y));
        if(y == -1)root = x;
        else {add(x,y);add(y,x);}
    }
    dep[root] = 1;
    dfs(root,root);
    for(int j = 1;j <= 20;j++)
        for(int i = 1;i <= maxx;i++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    m = read();
    for(int i = 1;i <= m;i++){
        x = read(); y = read();
        printf("%d\n",LCA(x,y));
    }
    return 0;
}