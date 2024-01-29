#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch =getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, k;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int wei  =0):to(to),nexte(ne),wei(wei){}
}e[maxn << 1];
int head[maxn], tot;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int dis[maxn], fa[maxn], p, dep[maxn];
bool book[maxn];
void dfs(int u,int f){
    fa[u] = f;dep[u] = dep[f] + 1;
    if(dis[u] > dis[p])p = u;
    for(int i = head[u];i;i = e[i].nexte){
        int v=  e[i].to, w = e[i].wei;
        if(book[v] || v == f)continue;
        dis[v] = dis[u] + w;dfs(v, u);
    }
}

signed main(){
    n = read(); k = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u, v, w); add(v, u, w);
    }
    int ans = 0x3f3f3f3f;
    dis[1] = 0;dfs(1, 0);dis[p] = 0;dfs(p, 0);
    // puts("11111");
    for(int i = p, j = p;i;i = fa[i]){
        while(dep[j] - dep[i] >= k)j = fa[j];
        ans = min(ans,max(dis[p] - dis[j],dis[i]));
    }
    // puts("22222");
    for(int i = p;i;i = fa[i])book[i] = 1;
    for(int i = p;i;i = fa[i])
        dis[p = i] = 0, dfs(i,fa[i]);
    // puts("33333");
    for(int i = 1;i <= n;i++)ans = max(ans,dis[i]);
    printf("%d\n",ans);
    return 0;
}