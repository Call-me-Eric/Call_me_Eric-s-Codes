#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, a[maxn];

int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int to = 0,int ne = 0):topoint(to),nextedge(ne){}
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]); head[u] = tot;}

int fa[maxn], son[maxn], size[maxn], dep[maxn];
void dfs1(int u,int f){
    size[u] = 1;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        fa[v] = u; dep[v] = dep[u] + 1;
        dfs1(v,u);
        size[u] += size[v];
        son[u] = size[v] > size[son[u]] ? v : son[u];
    }
}
int id[maxn], rev[maxn], top[maxn], ind;
void dfs2(int u,int t){
    id[u] = ++ind;rev[ind] = u; top[u] = t;
    if(!son[u])return;
    dfs2(son[u], t);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u] || v == son[u])continue;
        dfs2(v,v);
    }
}

struct node{
    int l, r, summ, tag;//tag是该区间需要加的数字
    node(int l = 0,int r = 0,int s = 0,int t = 0):l(l),r(r),summ(s),tag(t){}
}d[maxn << 2];
node mergenode(node l,node r){return node(l.l,r.r,l.summ + r.summ);}
void pushdown(int p){
    if(d[p].l != d[p].r && d[p].tag){
        d[p << 1].tag += d[p].tag;
        d[p << 1].summ += (d[p << 1].r - d[p << 1].l + 1) * d[p].tag;
        d[p << 1 | 1].tag += d[p].tag;
        d[p << 1 | 1].summ += (d[p << 1 | 1].r - d[p << 1 | 1].l + 1) * d[p].tag;
        d[p].tag = 0;
    }
}
void build(int l,int r,int p){
    if(l == r){d[p] = node(l,r,0,0);return;}
    int mid = l + r >> 1; build(l,mid,p << 1);build(mid + 1,r, p << 1 | 1);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}
void update(int l,int r,int p,int upd){
    if(l <= d[p].l && d[p].r <= r){d[p].tag += upd;d[p].summ += (d[p].r - d[p].l + 1) * upd;return;}
    pushdown(p); int mid = d[p].l + d[p].r >> 1;
    if(l <= mid)update(l,r,p << 1,upd);
    if(mid < r)update(l,r,p << 1 | 1,upd);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}
int query(int goal,int p){
    if(d[p].l == goal && d[p].r == goal)return d[p].summ;
    int mid = d[p].l + d[p].r >> 1;
    if(goal <= mid)return query(goal, p << 1);
    else return query(goal,p << 1 | 1);
}

void upd(int l,int r,int up){
    int u = l, v = r;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        update(id[top[u]],id[u],1,1);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u,v);
    update(id[u],id[v],1,1);
}

signed main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    n = read();int u, v;
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    dfs1(a[1],0); dfs2(a[1],a[1]); build(1,n,1);
    for(int i = 1;i < n;i++){upd(a[i],a[i + 1],1);}
    for(int i = 1;i <= n;i++)printf("%d\n",query(id[i],1) + ((i == a[1]) ? 0 : -1));
    return 0;
}