#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0 , f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a[maxn], b[maxn];
int n;bool book[maxn];
struct edge{
    int to, nexte;long double wei;
    edge(int to = 0,int ne = 0,long double wei = 0):to(to),nexte(ne),wei(wei){}
}e[maxn << 1];
int tot, head[maxn];
void add(int u,int v,long double w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
long double f[maxn];
void dfs(int u,int fa){
    book[u] = 1;f[u] = b[u] - a[u];
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == fa)continue;
        dfs(v, u);
        if(f[v] < 0)f[u] += f[v] * e[i].wei;
        else f[u] += f[v];
    }
}

signed main(){
    n = read(); int u, v, w;
    for(int i = 1;i <= n;i++)b[i] = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 2;i <= n;i++){v = read(); w = read();u = i;add(v, u, w);}
    dfs(1, 0);
    if(f[1] < 0)puts("NO");
    else puts("YES");
    return 0;
}