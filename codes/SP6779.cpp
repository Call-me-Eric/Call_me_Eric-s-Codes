#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m;
vector<int> edg[maxn];
int val[maxn];

int fa[maxn], dep[maxn], top[maxn],siz[maxn],son[maxn];
int dfn[maxn], idx, rev[maxn];
void dfs1(int u,int f){
    fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1;
    for(int v : edg[u])
        if(v != f){
            dfs1(v, u); siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
}
void dfs2(int u,int t){
    dfn[u] = ++idx;rev[idx] = u;
    top[u] = t; if(!son[u])return; dfs2(son[u], t);
    for(int v : edg[u])
        if(v != fa[u] && v != son[u])
            dfs2(v,v);
}

struct node{
    int lmax, rmax, summ, maxx;
    int l, r, tag;
    node(int lmax = 0,int rmax = 0,int summ = 0,int maxx = 0
        ,int l = 0,int r = 0,int tag = INF):lmax(lmax),rmax(rmax),summ(summ),maxx(maxx),l(l),r(r),tag(tag){}
};
node mergenode(node l,node r){return node(max(l.lmax,l.summ + r.lmax),max(r.rmax,l.rmax + r.summ)
    ,l.summ + r.summ,max(l.rmax + r.lmax,max(l.maxx,r.maxx)),l.l,r.r);}
struct Segment_Tree{
    node d[maxn << 2];
    void gettag(int p,int tag){
        d[p].lmax = d[p].rmax = d[p].maxx = max((tag * (d[p].r - d[p].l + 1)),tag);
        d[p].summ = (d[p].r - d[p].l + 1) * tag;
        d[p].tag = tag;
    }
    void pushdown(int p){
        if(d[p].tag != INF){
            gettag(p << 1,d[p].tag);gettag(p << 1 | 1,d[p].tag);
            d[p].tag = INF;
        }
    }
    void build(int l,int r,int p){
        if(l == r){gettag(p,val[rev[l]]);d[p].l = l;d[p].r = r;d[p].tag = INF;return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){gettag(p,upd);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;

int query(int u,int v){
    node ans1 = node(), ans2 = node(), tmp = node();
    while(top[u] != top[v]){
        if(dep[fa[top[u]]] < dep[fa[top[v]]]){swap(u, v);swap(ans1,ans2);}
        tmp = tree.query(dfn[top[u]],dfn[u]);
        // printf("=%d,%d,%d,%d\n",tmp.lmax,tmp.rmax,tmp.maxx,tmp.summ);
        ans1 = mergenode(tmp,ans1); u = fa[top[u]];
    }
    if(dep[u] < dep[v]){swap(u, v);swap(ans1,ans2);}
    tmp = tree.query(dfn[v],dfn[u]);swap(ans2.lmax,ans2.rmax);
        // printf("=%d,%d,%d,%d\n",tmp.lmax,tmp.rmax,tmp.maxx,tmp.summ);
    return mergenode(ans2,mergenode(tmp,ans1)).maxx;
}
void update(int u,int v,int x){
    while(top[u] != top[v]){
        if(dep[fa[top[u]]] < dep[fa[top[v]]])swap(u, v);
        tree.update(dfn[top[u]],dfn[u],x);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v])swap(u, v);
    tree.update(dfn[v],dfn[u],x);
}

signed main(){
    n = read();int opt, u, v;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v); edg[v].push_back(u);
    }
    dfs1(1,0);dfs2(1,1);tree.build(1,n,1);
    // for(int i = 1;i <= n;i++){printf("dfn[%d]=%d\n",i,dfn[i]);}
    m = read();
    for(int i = 1;i <= m;i++){
        opt = read();u = read(); v = read();
        if(opt == 1)printf("%d\n",query(u, v));
        else update(u, v, read());
    }
    return 0;
}
/*
15
1 -1 -4 5 4 -1 1 -9 1 -9 1 9 8 1 0 
1 2
1 3
3 4
4 5
5 6
1 9 
9 10
9 11
9 12
11 13
13 14
13 15
2 7
2 8

*/