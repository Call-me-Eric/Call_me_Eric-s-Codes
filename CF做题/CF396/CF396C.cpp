#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10, mod = 1e9 + 7;

int n, m;
vector<int> edg[maxn];
int dep[maxn],siz[maxn], son[maxn], fa[maxn];
int dfn[maxn], idx, top[maxn];
int rev[maxn];//idx[dfn[u]] = u;
void dfs1(int u,int f){
    siz[u] = 1;
    for(int v : edg[u]){
        if(v != f){
            fa[v] = u; dep[v] = dep[u] + 1;
            dfs1(v, u); siz[u] += siz[v];
            son[u] = siz[son[u]] > siz[v] ? son[u] : v;
        }
    }
}
void dfs2(int u,int t){
    rev[dfn[u] = ++idx] = u;top[u] = t;
    if(!son[u])return; dfs2(son[u],t);
    for(int v : edg[u])if(v != fa[u] && v != son[u])dfs2(v, v);
}

struct Segment_Tree{
    struct node{
        int summ1, summ2, summ3;
        int tag, l, r;//tag for summ3
        node(int s1 = 0,int s2 = 0,int s3 = 0,int l = 0,int r = 0,int tag = 0):summ1(s1),summ2(s2),summ3(s3),tag(tag),l(l),r(r){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.summ1 + r.summ1,l.summ2 + r.summ2,l.summ3 + r.summ3,l.l,r.r);}
    void pushdown(int p){
        if(d[p].tag != 0){
            d[p << 1].tag += d[p].tag; d[p << 1].summ3 += (d[p << 1].r - d[p << 1].l + 1) * d[p].tag;
            d[p << 1 | 1].tag += d[p].tag; d[p << 1 | 1].summ3 += (d[p << 1 | 1].r - d[p << 1 | 1].l + 1) * d[p].tag;
            d[p << 1].tag %= mod;d[p << 1].summ3 %= mod;d[p << 1 | 1].tag %= mod;d[p << 1 | 1].summ3 %= mod;
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0,0,0,l,l);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r){
            d[p].summ1 += upd;d[p].summ2 += upd * dep[rev[l]];
            d[p].summ1 %= mod;d[p].summ2 %= mod; return;
        }
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        // printf("l = %lld, r = %lld, s = %lld, t = %lld\n",l,r,s,t);
        if(s <= l && r <= t){
            d[p].summ3 += (r - l + 1) * upd;d[p].tag += upd;
            d[p].summ3 %= mod;d[p].tag %= mod; return;
        }
        int mid = l + r >> 1; pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int pos,int upd){update(1,n,pos,1,upd);}
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;

signed main(){
    n = read();int u , v, opt, w;
    for(int i = 2;i <= n;i++){
        u = read();edg[i].push_back(u);edg[u].push_back(i);
    }
    dep[1] = 1; dfs1(1, 1);dfs2(1, 1);tree.build(1,n,1);
    // for(int i = 1;i <= n;i++){
    //     printf("%lld %lld %lld %lld %lld %lld %lld\n",i,dep[i],fa[i],son[i],siz[i],dfn[i],top[i]);
    // }
    m = read();
    for(int i = 1;i <= m;i++){
        opt = read();u = read();
        if(opt == 1){
            v = read(); w = read();tree.update(dfn[u],w);
            tree.update(dfn[u],dfn[u] + siz[u] - 1,v);
        }
        else{
            int summ1 = 0, summ2 = 0;v = u;
            Segment_Tree::node tmp;
            int summ3 = tree.query(dfn[u],dfn[u]).summ3 % mod;
            while(u){
                tmp = tree.query(dfn[top[u]],dfn[u]);
                summ1 += tmp.summ1;summ2 += tmp.summ2;
                u = fa[top[u]];summ1 %= mod;summ2 %= mod;
            }
            // printf("%lld %lld %lld\n",summ1,summ2,summ3);
            summ1 = (summ3 + summ2 - summ1 * dep[v]) % mod;
            while(summ1 < 0)summ1 += mod;
            printf("%lld\n",summ1);
        }
    }
    return 0;
}