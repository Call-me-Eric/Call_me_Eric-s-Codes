#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e2 + 10;
int n, k;
int val[maxn];

struct edge{
    int to, nexte, wei;
    edge(int to  =0,int ne = 0,int we = 0):to(to),nexte(ne), wei(we){}
}e[maxn << 1];
int head[maxn], tot;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
int stk[maxn], top;
int f[maxn][maxn][maxn], g[maxn][maxn][maxn];
int dep[maxn];
void dfs(int u,int fa){
    stk[++top] = u;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].wei;
        dep[v] = dep[u] + w; dfs(v, u);
        for(int j = 1;j <= top;j++){
            for(int K = k;K + 1;K--){
                f[u][stk[j]][K] += f[v][stk[j]][0];
                g[u][stk[j]][K] += f[v][u][0];
                for(int x = 0;x <= K;x++){
                    f[u][stk[j]][K] = min(f[u][stk[j]][K],f[u][stk[j]][K - x] + f[v][stk[j]][x]);
                    g[u][stk[j]][K] = min(g[u][stk[j]][K],g[u][stk[j]][K - x] + f[v][u][x]);
                }
            }
        }
    }
    for(int j = 1;j <= top;j++){
        for(int K = 0;K <= k;K++){
            if(K > 0)f[u][stk[j]][K] = min(f[u][stk[j]][K] + val[u] * (dep[u] - dep[stk[j]]),g[u][stk[j]][K - 1]);
            else f[u][stk[j]][K] += val[u] * (dep[u] - dep[stk[j]]);
        }
    }
    top--;
}
signed main(){
    n = read(); k = read();
    for(int i = 1;i <= n;i++){val[i] = read();int v = read(), w = read(); add(v, i, w);}
    dfs(0,0); printf("%d\n",f[0][0][k]);
    return 0;
}