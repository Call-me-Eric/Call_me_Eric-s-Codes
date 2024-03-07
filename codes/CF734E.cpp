#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 2e5 + 10;
int col[maxn];

int head[maxn], tot;
struct edge{int topoint, nextedge, weight;
edge(int to = 0,int ne = 0,int we = 0):topoint(to),nextedge(ne),weight(we){}}e[maxn * 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int ans, f[maxn];
void dp(int u,int fa){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(v == fa)continue;
        dp(v,u);
        ans = max(ans,f[u] + f[v] + w);
        f[u] = max(f[u],f[v] + w);
    }
}
signed main(){
    n = read(); int u, v;
    for(int i = 1;i <= n;i++){col[i] = read();}
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        if(col[u] == col[v]){add(u,v,0); add(v,u,0);}
        else {add(u,v,1); add(v,u,1);}
    }
    dp(1,0);
    printf("%d\n",(ans + 1) / 2);
    return 0;
}