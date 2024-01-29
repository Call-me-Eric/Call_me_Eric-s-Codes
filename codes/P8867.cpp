#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, maxm = 1e6 + 10, mod = 1e9 + 7;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int topoint,nextedge;
    edge(int t = 0,int n = 0):topoint(t),nextedge(n){}
}e[maxm * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dfn[maxn], low[maxn], ind;
bool bridge[maxm * 2];
void Tarjan(int u,int inedge){
    dfn[u] = low[u] = ++ind;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v,i);
            if(dfn[u] < low[v])bridge[i] = bridge[i ^ 1] = true;
            low[u] = min(low[u],low[v]);
        }
        else if(i != (inedge ^ 1))low[u] = min(low[u],dfn[v]);
    }
}
int col[maxn], color;
int totedge[maxn], power[maxm * 2], totnode[maxn];
void dfs(int u){
    col[u] = color; totnode[color]++;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(col[v] || bridge[i])continue;
        dfs(v);
    }
}

edge e2[maxm * 2];
int head2[maxn], tot2 = 1;
void add2(int u,int v){e2[++tot2] = edge(v,head2[u]);head2[u] = tot2;}
int ans, f[maxn], sum[maxn];
void dfs2(int u, int fa){
    f[u] = power[totnode[u] + totedge[u]] % mod;
    sum[u] = totedge[u];
    for(int i = head2[u];i;i = e2[i].nextedge){
        int v = e2[i].topoint;
        if(v == fa)continue;
        dfs2(v,u);
        sum[u] += sum[v] + 1;
        f[u] = f[u] * ((f[v] + power[sum[v] + 1]) % mod) % mod;
    }
    f[u] = (f[u] - power[sum[u]] + mod) % mod;
    ans = (ans + f[u] * power[m - sum[u] - (fa != 0)] % mod) % mod;
}

signed main(){
    n = read(); m = read(); int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    for(int i = 1;i <= n;i++) if(!dfn[i]) Tarjan(i,0);
    for(int i = 1;i <= n;i++) if(!col[i]){color++;dfs(i);}
    for(int u = 1;u <= n;u++){
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(col[u] == col[v])totedge[col[u]]++;
            else add2(col[u],col[v]);
        }
    }
    power[0] = 1;
    for(int i = 1;i <= n + m;i++)power[i] = (power[i - 1] << 1) % mod;
    for(int i = 1;i <= color;i++)totedge[i] >>= 1;
    dfs2(1, 0);
    printf("%lld\n",ans % mod);
    return 0;
}