#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e4 + 10, maxm = 1e5 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int topoint = 0,int nextedge = 0,int weight = 0){
        this->topoint = topoint;
        this->nextedge = nextedge;
        this->weight = weight;
    }
}e[maxm];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

stack<int> stk;
int dfn[maxn], low[maxn], ind;
int col[maxn], color, size[maxn];
void Tarjan(int u){
    stk.push(u);
    dfn[u] = low[u] = ++ind;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(!col[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(dfn[u] == low[u]){
        int v = 0;color++;
        do{
            v = stk.top();stk.pop();
            col[v] = color;
            size[color]++;
        }while(v != u);
    }
}
int ans[maxn];
signed main(){
    while(scanf("%d %d",&n,&m) == 2 && (n || m)){
        tot = color = ind = 0;
        memset(ans,0x3f,sizeof(ans));int u, v, w;
        memset(e,0,sizeof(e)); memset(head,0,sizeof(head));
        memset(col,0,sizeof(col)); memset(dfn,0,sizeof(dfn));
        for(int i = 1;i <= m;i++){
            u = read() + 1; v = read() + 1; w = read();
            add(u,v,w);
        }
        for(int i = 1;i <= n;i++){if(!dfn[i]) Tarjan(i);}
        for(int u = 1;u <= n;u++)
            for(int i = head[u];i;i = e[i].nextedge){
                int v = e[i].topoint, w = e[i].weight;
                if(col[u] != col[v]){
                    ans[col[v]] = min(ans[col[v]],w);
                }
            }
        long long res = 0;
        for(int i = 1;i <= color;i++){
            res += ans[i] != 0x3f3f3f3f ? ans[i] : 0;
        }
        printf("%lld\n",res);
    }
    return 0;
}