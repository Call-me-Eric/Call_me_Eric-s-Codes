#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
int val[maxn];
vector<int> edg[maxn];

struct Matrix{
    int a[2][2];
    Matrix(int x = 0,int b = 0,int c = 0,int d = 0
    ){a[0][0] = x;a[0][1] = b;a[1][0] = c;a[1][1] = d;}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        c.a[0][0] = min(a.a[0][0] + b.a[0][0],a.a[0][1] + b.a[1][0]);
        c.a[0][1] = min(a.a[0][0] + b.a[0][1],a.a[0][1] + b.a[1][1]);
        c.a[1][0] = min(a.a[1][0] + b.a[0][0],a.a[1][1] + b.a[1][0]);
        c.a[1][1] = min(a.a[1][0] + b.a[0][1],a.a[1][1] + b.a[1][1]);
        return c;
    }
}mtx[maxn];

int siz[maxn], son[maxn], dep[maxn], fa[maxn];
void dfs1(int u,int f){
    fa[u] = f;siz[u] = 1;dep[u] = dep[f] + 1;
    for(int v : edg[u]){
        if(v != f){
            dfs1(v, u);siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
    }
}
int f[maxn];
int dfn[maxn], rev[maxn], idx, end[maxn], top[maxn];
void dfs2(int u,int t){
    dfn[u] = ++idx;rev[idx] = u;top[u] = t; end[t] = idx;
    f[u] = 0;
    mtx[u] = Matrix(0,val[u],0x3f3f3f3f,0);
    if(!son[u]){f[u] = val[u];mtx[u].a[0][0] = 0x3f3f3f3f;return;} dfs2(son[u],t);
    f[u] += f[son[u]];
    for(int v : edg[u])if(v != fa[u] && v != son[u]){
        dfs2(v,v); f[u] += f[v]; mtx[u].a[0][0] += f[v];
    }
    f[u] = min(f[u],val[u]);
}

struct Segment_Tree{
    struct node{
        Matrix sum;
        node(Matrix sum = Matrix()):sum(sum){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum * r.sum);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(mtx[rev[l]]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,Matrix upd){
        if(l == r && l == pos){d[p] = node(upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int pos,Matrix upd){update(1,n,pos,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
void update(int u,int w){
    mtx[u].a[0][1] += w;val[u] += w;
    Matrix x, y;
    while(u){
        x = tree.query(dfn[top[u]],end[top[u]]).sum;
        tree.update(dfn[u],mtx[u]);
        y = tree.query(dfn[top[u]],end[top[u]]).sum;
        u = fa[top[u]];
        mtx[u].a[0][0] += min(y.a[0][1],y.a[0][0]) - min(x.a[0][1],x.a[0][0]);
    }
}
int getans(int u){
    Matrix tmp = tree.query(dfn[u],end[top[u]]).sum;
    return min(tmp.a[0][0],tmp.a[0][1]);
}
void main(){
    n = read(); int u , v;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs1(1,0);dfs2(1,1);tree.build(1,n,1);
    m = read();char opt[10];
    for(int i = 1;i <= m;i++){
        scanf("%s",opt + 1);u = read();
        if(opt[1] == 'Q'){printf("%lld\n",getans(u));}
        else{v = read();update(u,v);}
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