#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 310;
int n, m, indegree[maxn];
int head[maxn], tot, score[maxn], f[maxn * 2][maxn * 2];
struct edge{
    int nextedge, topoint;
}e[maxn * 2];
void add(int u,int v){
    indegree[v]++;
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    head[u] = tot;
}
void dp(int x){
    for(int i = head[x];i;i = e[i].nextedge){
        int v = e[i].topoint;
        dp(v);
        for(int t = m;t > 0;t--){
            for(int j = 0;j < t;j++){
                f[x][t] = max(f[x][t],f[x][t - j] + f[v][j]);
            }
        }
    }
}
int main(){
    int u, v;
    n = read(); m = read();
    m++;
    for(int i = 1;i <= n;i++){
        u = read(); f[i][1] = read();
        add(u,i);
    }
    dp(0);
    printf("%d\n",f[0][m]);
    return 0;
}