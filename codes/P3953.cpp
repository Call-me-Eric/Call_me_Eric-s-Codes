#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, k, mod;
const int maxn = 1e5 + 10, maxm = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int head[maxn] ,tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int t = 0,int n = 0,int w = 0):topoint(t),nextedge(n),weight(w){}
}e[maxm];
void add(int u,int v,int w){e[++tot] = edge(v, head[u],w);head[u] = tot;}
int revhead[maxn], revtot;
edge reve[maxm];
void revadd(int u,int v,int w){reve[++revtot] = edge(v,revhead[u],w);revhead[u] = revtot;}

int dis[maxn];
struct node{int dis,id;node(int d = 0,int i = 0):dis(d),id(i){}};
bool operator < (node a,node b){return a.dis > b.dis;}
priority_queue<node> que;

int dp[maxn][51]; bool book[maxn][51], flag = false;
int dfs(int u,int k){
    if(dp[u][k] != -1)return dp[u][k];
    dp[u][k] = 0; book[u][k] = 1;
    for(int i = revhead[u];i;i = reve[i].nextedge){
        int v = reve[i].topoint, w = reve[i].weight;
        int x = dis[u] - dis[v] + k - w;
        if(x < 0)continue;
        if(book[v][x])flag = true;
        dp[u][k] = (dp[u][k] + dfs(v,x)) % mod;
    }
    book[u][k] = false;
    return dp[u][k];
}

signed main(){
int T = read();
while(T--){
    n = read(); m = read(); k = read(); mod = read(); int u, v, w;
    memset(head,0,sizeof(head)); tot = 0;
    memset(dp,-1,sizeof(dp)); flag = false;
    for(int i = 1;i <= n;i++){dis[i] = INF;}
    memset(revhead,0,sizeof(revhead)); revtot = 0;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u ,v ,w); revadd(v, u, w);
    }
    dis[1] = 0; que.push(node(0,1));
    while(!que.empty()){
        node tmp = que.top(); que.pop();
        int val = tmp.dis, u = tmp.id;
        if(val > dis[u])continue;
        for(int i = head[u]; i; i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                que.push(node(dis[v],v));
            }
        }
    }
    for(int i = 0;i <= k;i++)dfs(n,i);
    if(flag){puts("-1");continue;}
    int ans = 0;
    memset(dp,-1,sizeof(dp));dp[1][0] = 1;
    for(int i = 0;i <= k;i++){
        ans = (ans + dfs(n,i)) % mod;
    }
    printf("%lld\n",ans);
}
    return 0;
}