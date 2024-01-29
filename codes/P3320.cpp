#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;

int head[maxn], tot;
struct edge{int to, nexte, wei;edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int fa[maxn][21], dist[maxn], dep[maxn], dfn[maxn], idx, inv[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx; dep[u] = dep[f] + 1;inv[idx] = u;
    for(int i = 1;i <= 20;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].wei;
        if(v == f)continue;
        fa[v][0] = u; dist[v] = w + dist[u];
        dfs(v,u);
    }
}

int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v]){
            u = fa[u][i];
        }
    }
    if(u == v)return u;
    for(int i = 20;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i]; v = fa[v][i];
        }
    }
    return fa[u][0];
}
int dis(int u,int v){return dist[u] + dist[v] - 2 * dist[LCA(u,v)];}

bool book[maxn];
int ans;
set<int> st;

signed main(){
    n = read(); m = read(); int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u, v, w); add(v, u, w);
    }
    dfs(1,0);
    for(int i = 1;i <= m;i++){
        u = read();
        if(!book[u])st.insert(dfn[u]);
        auto it = st.begin();
        v = inv[(it = st.lower_bound(dfn[u])) == st.begin() ? *--st.end() : *--it];
        w = inv[(it = st.upper_bound(dfn[u])) == st.end() ? *st.begin() : *it];
        if(book[u])st.erase(dfn[u]);
        ans += (!book[u] ? 1 : -1) * (dis(u,v) + dis(u,w) - dis(v,w));
        book[u] ^= 1; printf("%lld\n",ans);
    }
    return 0;
}