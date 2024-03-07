#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, root, mod;
const int maxn = 1e5 + 10, maxm = 1e5 + 10;

int head[maxn], tot, weight[maxn];
struct edge{
    int topoint, nextedge;
    edge(int to = 0,int ne = 0):topoint(to),nextedge(ne){}
}e[maxm * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int size[maxn], fa[maxn], dep[maxn], son[maxn];
void dfs1(int u,int f){
    size[u] = 1;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        dep[v] = dep[u] + 1; fa[v] = u;
        dfs1(v,u); size[u] += size[v];
        son[u] = (size[v] > size[son[u]]) ? v : son[u];
    }
}
int top[maxn], id[maxn], rev[maxn], total;
void dfs2(int u,int t){
    top[u] = t;
    id[u] = ++total;
    rev[total] = u;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v != fa[u] && v != son[u])
            dfs2(v,v);
    }
}

int a[maxn << 2], lazy[maxn << 2];
int res = 0;
void pushdown(int p,int len){
    lazy[p << 1]     += lazy[p];
    lazy[p << 1 | 1] += lazy[p];
    a[p << 1]     += lazy[p] * (len - (len >> 1));
    a[p << 1 | 1] += lazy[p] * (len >> 1);
    a[p << 1] %= mod; a[p << 1 | 1] %= mod;
    lazy[p] = 0;
}
void build(int l,int r,int p){
    if(l == r){a[p] = weight[rev[l]] % mod;return;}
    int mid = l + r >> 1;
    build(l, mid, p << 1); build(mid + 1,r, p << 1 | 1);
    a[p] = a[p << 1] + a[p << 1 | 1];
}
void query(int l,int r,int s,int t,int p){
    if(s <= l && r <= t){res += a[p];res %= mod; return;}
    if(lazy[p])pushdown(p,r - l + 1);
    int mid = l + r >> 1;
    if(s <= mid)query(l,mid,s,t,p << 1);
    if(mid < t)query(mid + 1,r,s,t,p << 1 | 1);
}
void update(int l,int r,int s,int t,int p,int k){
    if(s <= l && r <= t){lazy[p] += k; a[p] += k * (r - l + 1);return;}
    if(lazy[p])pushdown(p,r - l + 1);
    int mid = l + r >> 1;
    if(s <= mid)update(l, mid, s, t, p << 1, k);
    if(mid < t)update(mid + 1, r, s, t, p << 1 | 1,k);
    a[p] = (a[p << 1] + a[p << 1 | 1]) % mod;
}

int qrange(int x,int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]])swap(x,y);
        res = 0;
        query(1,n,id[top[x]], id[x], 1);
        ans += res; ans %= mod;
        x = fa[top[x]];
    }
    if(dep[x] > dep[y])swap(x,y);
    res = 0; query(1,n,id[x],id[y],1); ans += res;
    return ans % mod;
}
void updrange(int x,int y,int k){
    k %= mod;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]])swap(x,y);
        update(1,n,id[top[x]], id[x], 1, k);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y])swap(x,y);
    update(1,n,id[x],id[y],1,k);
}
int qson(int x){res = 0; query(1,n,id[x],id[x] + size[x] - 1,1); return res;}
void updson(int x,int k){update(1,n,id[x],id[x] + size[x] - 1,1,k);}

signed main(){
    n = read(); m = read(); root = read(); mod = read();
    for(int i = 1;i <= n;i++)weight[i] = read();
    int u, v, k, op;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    dep[root] = 1;
    dfs1(root,0); dfs2(root,root);
    build(1,n,1);
    for(int i = 1;i <= m;i++){
        op = read();
        if(op == 1){u = read(); v = read(); k = read();updrange(u,v,k);}
        else if(op == 2){u = read(); v = read(); printf("%d\n",qrange(u,v) % mod);}
        else if(op == 3){u = read(); v = read(); updson(u,v);}
        else if(op == 4){u = read(); printf("%d\n",qson(u) % mod);}
    }
    return 0;
}