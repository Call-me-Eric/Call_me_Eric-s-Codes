#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e5 + 10;

int head[maxn], tot, w[maxn];
struct edge{
    int topoint, nextedge;
    edge(int to = 0, int ne = 0):topoint(to),nextedge(ne){}
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]); head[u] = tot;}

int size[maxn], son[maxn], dep[maxn], fa[maxn];
void dfs1(int u,int f){
    size[u] = 1;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v,u);
        size[u] += size[v];
        son[u] = size[v] > size[son[u]] ? v : son[u];
    }
}
int top[maxn], id[maxn], rev[maxn], _index;
void dfs2(int u,int t){
    top[u] = t;
    id[u] = ++_index;
    rev[_index] = u;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v != fa[u] && v != son[u])dfs2(v,v);
    }
}

int a[maxn << 2], lcol[maxn << 2], rcol[maxn << 2], lazy[maxn << 2];
void pushdown(int p){
    if(lazy[p]){
        a[p << 1] = a[p << 1 | 1] = 1;
        lcol[p << 1] = rcol[p << 1] = lcol[p << 1 | 1] = rcol[p << 1 | 1] = lazy[p];
        lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
        lazy[p] = 0;
    }
}
void pushup(int p){
    a[p] = a[p << 1] + a[p << 1 | 1] - (rcol[p << 1] == lcol[p << 1 | 1] ? 1 : 0);
    lcol[p] = lcol[p << 1]; rcol[p] = rcol[p << 1 | 1];
}
void build(int l,int r,int p){
    if(l == r){a[p] = 1;lcol[p] = rcol[p] = w[rev[l]]; return;}
    int mid = l + r >> 1;
    build(l,mid,p << 1); build(mid + 1,r,p << 1 | 1);
    pushup(p);
}
void update(int l,int r,int s,int t,int p,int k){
    if(s <= l && r <= t){lazy[p] = k;a[p] = 1;lcol[p] = rcol[p] = k;return;}
    pushdown(p); int mid = l + r >> 1;
    if(s <= mid)update(l,mid,s,t,p << 1,k);
    if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,k);
    pushup(p);
}
int res,lc, rc;
void query(int l,int r,int s,int t,int p){
    if(l == s){lc = lcol[p];}if(r == t){rc = rcol[p];}
    if(s <= l && r <= t){res += a[p];return;}
    pushdown(p); int mid = l + r >> 1;
    if(s <= mid)query(l,mid,s,t,p << 1);
    if(mid < t)query(mid + 1,r,s,t,p << 1 | 1);
    pushup(p);
}

int qrange(int u,int v){
    int ans = 0, lxx = 0, rxx = 0;
    while(top[u] != top[v]){
        res = 0;
        if(dep[top[u]] < dep[top[v]]){swap(u,v);swap(lxx,rxx);}
        query(1,n,id[top[u]], id[u],1); ans += res;
        if(lc == lxx)ans--;
        u = fa[top[u]]; lxx = lc;
    }
    res = 0;
    if(dep[u] > dep[v]){swap(u,v); swap(lxx,rxx);}
    query(1,n,id[u],id[v],1);ans += res;
    if(lxx == lc)ans--;
    if(rxx == rc)ans--;
    return ans;
}
void updrange(int u,int v,int k){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        update(1,n,id[top[u]], id[u], 1, k);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u,v);
    update(1,n,id[u],id[v],1,k);
}

signed main(){
    n = read(); m = read();
    int u, v, k; char op;
    for(int i = 1;i <= n;i++){w[i] = read();}
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v); add(v,u);
    }
    dfs1(1,0); dfs2(1,1);
    build(1,n,1);
    for(int i = 1;i <= m;i++){
        op = getchar(); while(op == '\n' || op == ' ')op = getchar();
        u = read(); v = read();
        if(op == 'C'){k = read(); updrange(u,v,k);}
        else{printf("%d\n",qrange(u,v));}
    }
    return 0;
}