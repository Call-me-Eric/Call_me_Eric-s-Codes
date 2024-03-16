#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxm = 1e6 + 10,INF = 1e9;
int n, m;
struct edge{
    int u, v, w;int id;
    edge(int u = 0,int v = 0,int w = 0,int id = 0
    ):u(u),v(v),w(w),id(id){}
    friend bool operator < (edge a,edge b){return a.w < b.w;}
}e[maxm];
struct DSU{
    int fa[maxn];
    void init(int n){for(int i = 1;i <= n;i++)fa[i] = i;}
    int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
}dsu;
int fa[21][maxn], val[21][maxn];
int dep[maxn];
vector<pair<int,int> > edg[maxn];
void dfs(int u,int f){
    for(int i = 1;i <= 20;i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]], val[i][u] = max(val[i - 1][u],val[i - 1][fa[i - 1][u]]);
    for(auto i : edg[u]){
        int v = i.first, w = i.second;
        if(v != f){
            fa[0][v] = u;val[0][v] = w;dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
}
pair<int,int> LCA(int u,int v){
    int ans = -INF;
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            ans = max(ans,val[i][u]),u = fa[i][u];
    if(u == v){return make_pair(ans,u);}
    for(int i = 20;i + 1;i--){
        if(fa[i][u] != fa[i][v]){
            ans = max(ans,max(val[i][u],val[i][v]));
            u = fa[i][u];v = fa[i][v];
        }
    }
    ans = max(ans,max(val[0][u],val[0][v]));
    return make_pair(ans,fa[0][u]);
}
int ans[maxm];
int X[maxn];
bool book[maxm];
void main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(), v = read(), w = read();
        e[i] = edge(u,v,w,i);
    }
    dsu.init(n); sort(e + 1,e + 1 + m);
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= 20;j++)val[j][i] = -INF;
        X[i] = INF;
    }
    for(int i = 1;i <= m;i++){
        u = e[i].u;v = e[i].v;w = e[i].w;
        if(dsu.getf(u) != dsu.getf(v)){
            dsu.fa[dsu.getf(u)] = dsu.getf(v);
            edg[u].push_back(make_pair(v, w));
            edg[v].push_back(make_pair(u, w));
            book[i] = 1;
        }
    }
    dep[1] = 1;dfs(1,0);dsu.init(n);
    int cnt = 0;
    for(int i = 1;i <= m;i++){
        if(!book[i]){
            auto tmp = LCA(e[i].u,e[i].v);
            ans[e[i].id] = tmp.first;int lca = tmp.second;
            u = e[i].u, v = e[i].v, w = e[i].w;
            while(dep[dsu.getf(u)] > dep[lca]){
                cnt++;if(cnt >= 1e8)printf("adfskasjfjsadflkajsdlk fu = %d,dep[fu] = %d\n",dsu.getf(u),dep[dsu.getf(u)]);
                int x = dsu.getf(u); X[x] = w;
                dsu.fa[x] = dsu.getf(fa[0][x]);
            }
            while(dep[dsu.getf(v)] > dep[lca]){
                cnt++;if(cnt >= 1e8)printf("2398417895731247589437 fv = %d\n",dsu.getf(v));
                int x = dsu.getf(v); X[x] = w;
                dsu.fa[x] = dsu.getf(fa[0][x]);
            }
        }
    }
    for(int i = 1;i <= m;i++){
        if(book[i]){
            int u = e[i].u, v = e[i].v;
            if(dep[u] < dep[v]){swap(u,v);}
            ans[e[i].id] = X[u];
        }
    }
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}