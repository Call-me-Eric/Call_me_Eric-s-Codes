#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 6e3 + 10;
int r[maxn];
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int head[maxn], tot;
struct edge{
    int topoint,nextedge;
}e[maxn * 2];
int dp[maxn][2];
void add(int u,int v){
    e[++tot].topoint = v;
    e[tot].nextedge = head[u];
    head[u] = tot;
}
void dfs(int u,int fa){
    dp[u][0] = 0;
    dp[u][1] = r[u];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa)continue;
        dfs(v,u);
        dp[u][0] += max(0,max(dp[v][0],dp[v][1]));
        dp[u][1] += max(0,dp[v][0]);
    }
}
signed main(){
    n = read();
    int u, v;
    for(int i = 1;i <= n;i++){
        r[i] = read();
    }
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v); add(v,u);
    }
    dfs(1,0);
    printf("%d\n",max(dp[1][0],dp[1][1]));
    return 0;
}