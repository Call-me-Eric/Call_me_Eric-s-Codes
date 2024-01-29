#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m, q;

int fa[maxn], d[maxn];
int getf(int x){return x == fa[x] ? x : fa[x] = getf(fa[x]);}

vector<int> edg[maxn];
int dp[maxn][2];bool book[maxn];

void dfs(int u,int f){
    book[u] = 1;fa[getf(u)] = getf(f);
    for(int v : edg[u]){
        if(v != f){
            dfs(v,u);
            if(dp[v][0] + 1 > dp[u][0]){
                dp[u][1] = dp[u][0];
                dp[u][0] = dp[v][0] + 1;
            }
            else if(dp[v][0] + 1 > dp[u][1]){dp[u][1] = dp[v][0] + 1;}
        }
    }
}

signed main(){
    n = read(); m = read(); q = read();
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    
    for(int i = 1;i <= n;i++)if(!book[i])dfs(i, i);
    for(int i = 1;i <= n;i++){
        d[getf(i)] = max(d[getf(i)],dp[i][0] + dp[i][1]);
    }
    
    int opt, u, v;
    for(int i = 1;i <= q;i++){
        opt = read(); u = read();
        if(opt == 1){printf("%d\n",d[getf(u)]);}
        else{
            v = read();int fu = getf(u), fv = getf(v);
            if(fu == fv)continue;
            fa[fu] = fv;
            d[fv] = max(max(d[fv],d[fu]),(d[fu] + 1) / 2 + (d[fv] + 1) / 2 + 1);
        }
    }
    return 0;
}