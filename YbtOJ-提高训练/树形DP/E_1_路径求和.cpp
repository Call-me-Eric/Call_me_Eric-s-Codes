#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e5 + 10;
int ans = 0, cnt = 0;
int d[maxn], son[maxn], sum[maxn];
int head[maxn], tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int to = 0,int ne = 0,int we = 0):topoint(to),nextedge(ne),weight(we){}
}e[maxn * 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

void dfs(int u,int fa){
    sum[u] = 1; if(d[u] == 1) son[u] = 1, cnt++;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa)continue;
        dfs(v,u);
        son[u] += son[v];
        sum[u] += sum[v];
    }
}
void dfs1(int u,int fa){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(fa == v)continue;
        dfs1(v,u);
        ans += w * (son[v] * (n - sum[v]) + sum[v] * (cnt - son[v]));
    }
}
signed main(){
    int u, v , w;
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        w = read(); u = read(); v = read();
        d[u]++; d[v]++;
        add(u,v,w); add(v,u,w);
    }
    dfs(1,0); dfs1(1,0);
    printf("%lld\n",ans);
    return 0;
}