#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e4 + 10,maxm = 1e5 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int topoint = 0, int nextedge = 0){
        this->nextedge = nextedge;
        this->topoint = topoint;
    }
}e[maxm];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
int val[maxn];

int dfn[maxn], low[maxn], ind;
int col[maxn], color, totval[maxn];
stack<int> stk;
void Tarjan(int u){
    dfn[u] = low[u] = ++ind;
    stk.push(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(!col[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        int v = 0;color++;
        do{
            v = stk.top();stk.pop();
            col[v] = color;totval[color] += val[v];
        }while(u != v);
    }
}
int d[maxn], f[maxn];
edge e2[maxm];
int head2[maxn], tot2;
void add2(int u,int v){e2[++tot2] = edge(v,head2[u]);head2[u] = tot2;}

signed main(){
    int u, v;
    n = read(); m = read();
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u, v);
    }
    for(int i = 1;i <= n;i++)if(!dfn[i])Tarjan(i);
    for(int u = 1;u <= n;u++)
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(col[u] != col[v]){
                add2(col[u],col[v]);
                d[col[v]]++;
            }
        }
    queue<int> que;
    for(int i = 1;i <= color;i++)
        if(!d[i]){que.push(i);f[i] = totval[i];}
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head2[u];i;i = e2[i].nextedge){
            int v = e2[i].topoint;
            d[v]--;
            f[v] = max(f[v],f[u] + totval[v]);
            if(!d[v])que.push(v);
        }
    }
    int ans = 0;
    for(int i = 1;i <= color;i++)ans = max(f[i],ans);
    printf("%d\n",ans);
    return 0;
}