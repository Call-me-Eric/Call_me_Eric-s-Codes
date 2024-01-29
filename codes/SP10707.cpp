#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int col[maxn];
vector<int> tmp;
vector<int> edg[maxn];

int st[maxn], ed[maxn],idx;
int id[maxn];
int dep[maxn], fa[21][maxn];
void dfs(int u,int f){
    st[u] = ++idx;id[idx] = u;fa[0][u] = f;dep[u] = dep[f] + 1;
    for(int v : edg[u])if(v != f)dfs(v, u);
    ed[u] = ++idx;id[idx] = u;
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v]){
            u = fa[i][u];
            v = fa[i][v];
        }
    return fa[0][u];
}

bool book[maxn];
int cnt[maxn], ans, len, res[maxn];
inline void upd(int x){
    if(book[x]){ans -= !--cnt[col[x]];}
    else ans += !cnt[col[x]]++;
    book[x] ^= 1;
}
struct query{
    int l, r, id,lca;
    query(int l = 0,int r = 0,int id = 0,int lca = 0):l(l),r(r),id(id),lca(lca){}
    friend bool operator < (query a,query b){
        if(a.l / len != b.l / len)return a.l < b.l;
        return ((a.l / len) & 1) ? a.r < b.r : a.r > b.r;
    }
}qry[maxn];

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= n;i++)tmp.push_back(col[i] = read());
    for(int i = 1;i < n;i++){
        u = read();v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }

    sort(tmp.begin(),tmp.end());tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    for(int i = 1;i <= n;i++)col[i] = lower_bound(tmp.begin(),tmp.end(),col[i]) - tmp.begin();
    dfs(1, 1); len = sqrt(n * 2);
    for(int j = 1;j <= 20;j++)
        for(int i = 1;i <= n;i++)
            fa[j][i] = fa[j - 1][fa[j - 1][i]];

    for(int i = 1;i <= m;i++){
        int lca = LCA(u = read(), v = read());
        if(st[u] > st[v])swap(u, v);
        if(lca == u)qry[i] = query(st[u],st[v],i);
        else qry[i] = query(ed[u],st[v],i,lca);
    }
// puts("1111111");
    sort(qry + 1,qry + 1 + m);
// puts("2222222");
    int l = 1, r = 1;ans = 0;upd(id[1]);
    for(int i = 1;i <= m;i++){
        
        while(l > qry[i].l)upd(id[--l]);
        while(qry[i].r > r)upd(id[++r]);
        while(qry[i].l > l)upd(id[l++]);
        while(r > qry[i].r)upd(id[r--]);
        if(qry[i].lca)upd(qry[i].lca);
        res[qry[i].id] = ans;
        if(qry[i].lca)upd(qry[i].lca);
    }
    for(int i = 1;i <= m;i++){printf("%d\n",res[i]);}
    return 0;
}