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
const int maxn = 1e5 + 10;
int dep[maxn],dis[maxn], n, fa[21][maxn], m;
int L[maxn], R[maxn], idx, inv[maxn];
vector<int> edg[maxn];
void dfs(int u,int f){
    L[u] = ++idx;inv[idx] = u;fa[0][u] = f;
    for(int i = 1;i <= 20;i++){fa[i][u] = fa[i - 1][fa[i - 1][u]];}
    for(int v : edg[u])if(v != f){dep[v] = dep[u] + 1;dfs(v, u);}
    R[u] = idx;
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
struct Segment_Tree{
    struct node{
        int maxx, tag;
        node(int maxx = 0,int tag=  0):maxx(maxx),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag += d[p].tag; d[p << 1].maxx += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag; d[p << 1 | 1].maxx += d[p].tag;
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(dep[inv[l]]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].tag += upd;d[p].maxx += upd;return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(){build(1,n,1);}
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
struct LCT{
    struct node{
        int fa, ch[2];
        int tag;
    }d[maxn];
    #define FA(p) d[p].fa
    #define C(p,x) d[p].ch[x]
    inline void maintain(int p){}
    inline int get(int p){return C(FA(p),0) == p ? 0 : (C(FA(p),1) == p ? 1 : -1);}
    inline void connect(int p,int f,int x){FA(p) = f;if(x != -1)C(f,x) = p;maintain(f);}
    void pushdown(int p){if(d[p].tag){swap(C(p,0),C(p,1));d[C(p,0)].tag ^= 1,d[C(p,1)].tag ^= 1;d[p].tag = 0;}}
    void pushdownall(int p){if(get(p) != -1)pushdownall(FA(p));pushdown(p);}
    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u,y,chkx);connect(y,x,chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        pushdownall(p);
        for(int f = FA(p);f = FA(p),get(p) != -1;rotate(p))
            if(get(f) != -1)rotate(get(f) == get(p) ? f : p);
    }
    int findroot(int p){while(C(p,0))p = C(p,0);return p;}
    void access(int p){
        int rc = 0;
        while(p){
            splay(p);
            if(C(p,1)){int x = findroot(C(p,1));tree.update(L[x],R[x],1);}
            if(C(p,1) = rc){int x = findroot(rc);tree.update(L[x],R[x],-1);}
            maintain(p);rc = p;p = FA(p);
        }
    }
    #undef FA
    #undef C
}lct;
void main(){
    n = read(); m = read();int u, v, opt;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 1);tree.build();for(int i = 1;i <= n;i++)lct.d[i].fa = fa[0][i];lct.d[1].fa = 0;
    for(int i = 1;i <= m;i++){
        opt = read();u = read();
        if(opt == 1)lct.access(u);
        if(opt == 2){
            v = read();int lca=  LCA(u, v);
            printf("%d\n",tree.query(L[u],L[u]).maxx + tree.query(L[v],L[v]).maxx - 2 * tree.query(L[lca],L[lca]).maxx + 1);
        }
        if(opt == 3){printf("%d\n",tree.query(L[u],R[u]));}
    }
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