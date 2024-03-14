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
int n, m;
struct Matrix{
    int a[2][2]; Matrix(){}
    Matrix(int x1,int x2,int x3,int x4){a[0][0] = x1;a[0][1] = x2;a[1][0] = x3;a[1][1] = x4;}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        c.a[0][0] = max(a.a[0][0] + b.a[0][0],a.a[0][1] + b.a[1][0]);
        c.a[0][1] = max(a.a[0][0] + b.a[0][1],a.a[0][1] + b.a[1][1]);
        c.a[1][0] = max(a.a[1][0] + b.a[0][0],a.a[1][1] + b.a[1][0]);
        c.a[1][1] = max(a.a[1][0] + b.a[0][1],a.a[1][1] + b.a[1][1]);
        return c;
    }
}Mtx[maxn];
int f[maxn][2], g[maxn][2];
vector<int> edg[maxn];
int val[maxn];
int siz[maxn], son[maxn], dep[maxn], fa[maxn];
void dfs1(int u,int f){
    fa[u] = f; siz[u] = 1; dep[u] = dep[f] + 1;
    for(int v : edg[u])if(v != f){
        dfs1(v, u);siz[u] += siz[v];
        son[u] = siz[v] > siz[son[u]] ? v : son[u];
    }
}
int dfn[maxn], idx, top[maxn], end[maxn], rev[maxn];
void dfs2(int u,int t){
    dfn[u] = ++idx; top[u] = t;
    rev[idx] = u; end[t] = idx;
    f[u][0] = 0;f[u][1] = val[u];
    Mtx[u] = Matrix(0,0,val[u],-0x3f3f3f3f);
    if(!son[u])return; dfs2(son[u],t);
    f[u][0] += max(f[son[u]][0],f[son[u]][1]);
    f[u][1] += f[son[u]][0];
    for(int v : edg[u])if(v != fa[u] && v != son[u]){
        dfs2(v,v);
        f[u][0] += max(f[v][0],f[v][1]);
        f[u][1] += f[v][0];
        Mtx[u].a[0][0] += max(f[v][0],f[v][1]);
        Mtx[u].a[0][1] += max(f[v][0],f[v][1]);
        Mtx[u].a[1][0] += f[v][0];
    }
}
struct Segment_Tree{
    struct node{
        Matrix sum;
        node(Matrix sum = Matrix()):sum(sum){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum * r.sum);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(Mtx[rev[l]]);return;}
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
    Mtx[u].a[1][0] += w - val[u];val[u] = w;
    Matrix x, y;
    while(u){
        x = tree.query(dfn[top[u]],end[top[u]]).sum;
        tree.update(dfn[u],Mtx[u]);
        y = tree.query(dfn[top[u]],end[top[u]]).sum;
        u = fa[top[u]];
        Mtx[u].a[0][0] += max(y.a[0][0],y.a[1][0]) - max(x.a[0][0],x.a[1][0]);
        Mtx[u].a[0][1] += max(y.a[0][0],y.a[1][0]) - max(x.a[0][0],x.a[1][0]); 
        Mtx[u].a[1][0] += y.a[0][0] - x.a[0][0];
    }
}
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        int u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs1(1,0);dfs2(1,1);tree.build(1,n,1); int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        update(u,v);
        Matrix ans = tree.query(dfn[1],end[1]).sum;
        printf("%d\n",max(ans.a[0][0],ans.a[1][0]));
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
/*
5 3 
2 4 1 3 9 
1 5 
5 2 
5 3 
3 4 
*/