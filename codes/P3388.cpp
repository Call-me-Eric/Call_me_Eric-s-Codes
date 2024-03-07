#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 2e4 + 10, maxm = 1e5 + 10;

int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int t = 0,int n = 0):topoint(t),nextedge(n){}
}e[maxm * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]); head[u] = tot;}

int dfn[maxn], low[maxn], ind;
int cut[maxn];
void Tarjan(int u,int fa){
    dfn[u] = low[u] = ++ind;
    int cnt = 0;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v,fa);
            low[u] = min(low[u],low[v]);
            if(u != fa && low[v] >= dfn[u])cut[u] = 1;
            if(u == fa) cnt++;
        }
        low[u] = min(low[u],dfn[v]);
    }
    if(cnt > 1 && u == fa)cut[u] = 1;
}

signed main(){
    n = read(); m = read(); int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    for(int i = 1;i <= n;i++) if(!dfn[i]) Tarjan(i, i);
    int sum = 0; for(int i = 1;i <= n;i++) sum += cut[i];
    printf("%d\n",sum);
    for(int i = 1;i <= n;i++) if(cut[i]) printf("%d ",i);
    return 0;
}