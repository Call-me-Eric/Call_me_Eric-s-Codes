#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, maxm = 2e6 + 10;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int topoint, nextedge;
    edge(int t = 0,int n = 0):topoint(t),nextedge(n){}
}e[maxm * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dfn[maxn], low[maxn], ind;
bool cutedge[maxm * 2];
void Tarjan(int u,int inedge){
    dfn[u] = low[u] = ++ind;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v,i);
            if(dfn[u] < low[v])cutedge[i] = cutedge[i ^ 1] = true;
            low[u] = min(low[u],low[v]);
        }
        else if(i != (inedge ^ 1))low[u] = min(low[u], dfn[v]);
    }
}
int col[maxn], color;
vector<int> ans[maxn];
void dfs(int u){
    col[u] = color; ans[color].push_back(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(col[v] || cutedge[i])continue;
        dfs(v);
    }
}

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u,v);add(v,u);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i])Tarjan(i,0);
    for(int i = 1;i <= n;i++){
        if(!col[i]){
            color++;
            dfs(i);
        }
    }
    printf("%d\n",color);
    for(int i = 1;i <= color;i++){
        printf("%d ",ans[i].size());
        for(int j = 0;j < ans[i].size();j++)
            printf("%d ",ans[i][j]);
        puts("");
    }
    return 0;
}