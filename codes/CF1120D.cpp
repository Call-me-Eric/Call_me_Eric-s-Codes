#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f= -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, c[maxn];
vector<int> edg[maxn];

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

struct edge{
    int from, to, wei, id;
    edge(int fr = 0,int to = 0,int wei = 0,int id = 0):from(fr),to(to),wei(wei),id(id){}
    friend bool operator < (edge a,edge b){return a.wei < b.wei;}
}e[maxn];
int res = 0;bool book[maxn];
int dfn[maxn], low[maxn], idx;
void kruskal(){
    for(int i = 1;i <= n;i++)e[i].id = i;
    sort(e + 1,e + 1 + n);memset(book,0,sizeof(book));
    idx++; for(int i = 1;i <= idx;i++){fa[i] = i;}

    for(int i = 1,j = 1;i <= n;i = j){
        j = i;
        while(e[j].wei == e[i].wei && j <= n){
            int fu = getf(e[j].from), fv = getf(e[j].to);
            if(fu != fv){book[e[j].id] = 1;}j++;
        }
        j = i;
        while(e[j].wei == e[i].wei && j <= n){
            int fu = getf(e[j].from), fv = getf(e[j].to);
            if(fu != fv){fa[fu] = fv;res += e[j].wei;}
            j++;
        }
    }
}

void dfs(int u,int f){
    bool leaf = true;dfn[u] = 0x3f3f3f3f;
    for(int v : edg[u]){
        if(v != f){
            dfs(v, u);leaf = false;
            low[u] = max(low[u],low[v]); dfn[u] = min(dfn[u],dfn[v]);
        }
    }
    if(leaf){dfn[u] = low[u] = ++idx;}
    e[u] = edge(dfn[u],low[u] + 1,c[u]);
    return;
}

signed main(){
    n = read(); int u, v;
    for(int i = 1;i <= n;i++)c[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 0); kruskal();
    int cnt = 0;
    for(int i = 1;i <= n;i++){cnt += book[i];}
    printf("%lld %lld\n",res,cnt);
    for(int i = 1;i <= n;i++){if(book[i])printf("%lld ",i);}
    // puts("DEBUG");printf("idx=%lld\n",idx);
    // for(int i = 1;i <= n;i++)printf("i = %lld : dfn = %lld, low = %lld\n",i,dfn[i], low[i]);
    // for(int i = 1;i <= n;i++)printf("fr=%lld, to=%lld, wei =%lld\n",e[i].from,e[i].to,e[i].wei);
    return 0;
}