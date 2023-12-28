#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 110, maxm = 510;
int W[maxn], V[maxn];
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int topoint = 0, int nextedge = 0){
        this->topoint = topoint;
        this->nextedge = nextedge;
    }
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dfn[maxn], low[maxn], ind;stack<int> stk;
int col[maxn], color, colw[maxn],colv[maxn];
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
    if(dfn[u] == low[u]){
        int v = 0;color++;colw[color] = colv[color] = 0;
        do{
            v = stk.top();stk.pop();
            col[v] = color;
            colw[color] += W[v];
            colv[color] += V[v];
        }while(v != u);
    }
}

int d[maxn], dp[maxn][maxm];
queue<int> que;
vector<int> e2[maxn];
void dfs(int u){
    for(int i = colw[u];i <= m;i++)dp[u][i] = colv[u];
    for(int i = 0, len = e2[u].size();i < len;i++){
        int v = e2[u][i];
        dfs(v);
        if(m >= colw[u])
        for(int j = m - colw[u];j >= 0;j--){
            for(int k = 0;k <= j;k++)
            dp[u][j + colw[u]] = max(dp[u][j + colw[u]],dp[u][j + colw[u] - k] + dp[v][k]);
        }
    }
}
signed main(){
    n = read(); m = read(); int tmp;
    for(int i = 1;i <= n;i++)W[i] = read();
    for(int i = 1;i <= n;i++)V[i] = read();
    for(int i = 1;i <= n;i++){
        tmp = read();
        if(tmp)add(tmp,i);
    }
    for(int i = 1;i <= n;i++){if(!dfn[i])Tarjan(i);}
    for(int u = 1;u <= n;u++){
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(col[u] != col[v]){
                e2[col[u]].push_back(col[v]);
                d[col[v]]++;
            }
        }
    }
    for(int i = 1;i <= color;i++)
        if(!d[i]){e2[0].push_back(i);}
    dfs(0);
    printf("%d\n",dp[0][m]);
    return 0;
}