#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n;
int f[maxn][3], col[maxn];//f[0] = 无联通黑白点 f[1(01)] = 联通黑点 f[2(10)] = 联通白点

int head[maxn], tot;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

void dfs(int u,int fa){
    if(col[u])f[u][0] = f[u][col[u] ^ 3] = INF;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;if(v == fa)continue;
        dfs(v, u);
        f[u][0] += min(f[v][0],min(f[v][1],f[v][2]) + e[i].wei);
        f[u][1] += min(f[v][1],min(f[v][0],f[v][2] + e[i].wei));
        f[u][2] += min(f[v][2],min(f[v][0],f[v][1] + e[i].wei));
    }
}

signed main(){
    n = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u, v, w);add(v, u, w);
    }
    v = read(); for(int i = 1;i <= v;i++)col[read()] = 1;
    v = read(); for(int i = 1;i <= v;i++)col[read()] = 2;
    dfs(1, 0);
    printf("%lld\n",min(f[1][0],min(f[1][1],f[1][2])));
    return 0;
}