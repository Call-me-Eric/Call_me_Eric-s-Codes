#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1500;
int k[maxn], m[maxn];
int dp[maxn][3];//dp[i][0]->choose i itself dp[i][1]-> choose i's father dp[i][2]-> choose one of i's sons
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
}e[maxn * 2];
void add(int u,int v){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    head[u] = tot;
}
void dfs(int u,int fa){
    dp[u][0] = k[u];
    int minn = 0x3f3f3f3f;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa)continue;
        dfs(v,u);
        dp[u][0] += min(min(dp[v][0],dp[v][1]),dp[v][2]);
        dp[u][1] += min(dp[v][0],dp[v][2]);
        dp[u][2] += min(dp[v][0],dp[v][2]);
        minn = min(minn,dp[v][0] - min(dp[v][0],dp[v][2]));
    }
    dp[u][2] += minn;
}
signed main(){
    n = read();
    int t, tmp;
    for(int i = 1;i <= n;i++){
        t = read();
        k[t] = read();
        m[t] = read();
        for(int j = 1;j <= m[t];j++){
            tmp = read();
            add(t,tmp); add(tmp,t);
        }
    }
    dfs(1,0);
    printf("%lld\n",min(dp[1][0],dp[1][2]));
    return 0;
}