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
const int maxn = 2e5 + 10;
int n, m;
int val[maxn];
vector<int> edg[maxn];
int fa[maxn], siz[maxn], dep[maxn], son[maxn];
int idx, dfn[maxn], rev[maxn], top[maxn];
void dfs1(int u,int f){
    fa[u] = f;siz[u] = 1;dep[u] = dep[f] + 1;
    for(int v : edg[u]){
        if(v != f){
            dfs1(v, u);siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
    }
}
void dfs2(int u,int t){
    dfn[u] = ++idx;rev[idx] = u;top[u] = t;
    if(!son[u])return; dfs2(son[u],t);
    for(int v : edg[u])if(v != fa[u] && v != son[u])dfs2(v, v);
}
struct Segment_Tree{
    struct node{
        int minn, maxx;
        node(int minn = 0,int maxx = 0):minn(minn),maxx(maxx){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(min(l.minn,r.minn),max(l.maxx,r.maxx));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(val[rev[l]],val[rev[l]]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd,upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    
}tree;
void main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
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