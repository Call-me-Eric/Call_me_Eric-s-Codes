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
int n, q;
vector<int> edg[maxn];
int fa[21][maxn], siz[maxn], son[maxn], dep[maxn];
void dfs1(int u,int f){
    fa[0][u] = f;siz[u] = 1;dep[u] = dep[f] + 1;
    for(int i = 1;i <= 20;i++)fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(int v : edg[u]){
        if(v != f){
            dfs1(v, u); siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
    }
}
int dfn[maxn], low[maxn], idx, top[maxn], rev[maxn];
void dfs2(int u,int t){
    top[u] = t;dfn[u] = ++idx;rev[idx] = u;low[u] = siz[u] + dfn[u] - 1;
    if(!son[u])return; dfs2(son[u],t);
    for(int v : edg[u])if(v != fa[0][u] && v != son[u])dfs2(v,v);
}
struct Segment_Tree{
    struct node{
        int sum, l ,r, tag;
        node(int sum = 0,int l = 0,int r = 0,int tag = 0
        ):sum(sum),l(l),r(r),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum,l.l,r.r);}
    inline void change(int p,int tag){d[p].tag += tag;d[p].sum += (d[p].r - d[p].l + 1) * tag;}
    inline void pushdown(int p){change(p << 1,d[p].tag);change(p << 1 | 1,d[p].tag);d[p].tag = 0;}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0,l,r,0);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){change(p,upd);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1, upd);
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
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    int query(int l,int r){return query(1,n,l,r,1).sum;}
    int find(int l,int r,int p,int s){
        if(l == r)return l;
        int mid = l + r >> 1;pushdown(p);
        if(d[p << 1].sum >= s)return find(l,mid,p << 1,s);
        else return find(mid + 1,r,p << 1 | 1,s - d[p << 1].sum);
    }
}tree;
void main(){
    n = read();int u, v, opt;
    for(int i = 1;i < n;i++){
        u = read();v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs1(1, 0);dfs2(1,1);tree.build(1,n,1);
    // for(int i = 1;i <= n;i++)printf("i = %lld,dfn = %lld,low = %lld,siz = %lld,son = %lld\n",i,dfn[i],low[i],siz[i],son[i]);
    q = read();
    while(q--){
        opt = read(); u = read();
        if(opt == 1){tree.update(dfn[u],low[u],1);}
        else{
            v = read();
            while(top[u] != top[v]){
                if(dep[top[u]] < dep[top[v]])swap(u, v);
                tree.update(dfn[top[u]],dfn[u],1);
                u = fa[0][top[u]];
            }
            if(dfn[u] > dfn[v])swap(u, v);
            tree.update(dfn[u],dfn[v],1);
        }
        int sum = tree.d[1].sum / 2 + 1;
        u = rev[tree.find(1,n,1,sum)];
        if(tree.query(dfn[u],low[u]) >= sum){printf("%lld\n",u);continue;}
        // printf("q = %lld,u = %lld\n",q,u);
        for(int i = 20;i + 1;i--){
            if(fa[i][u] && tree.query(dfn[fa[i][u]],low[fa[i][u]]) < sum)
                u = fa[i][u];
            // printf("u = %lld,i = %lld\n",u,i);
        }
        printf("%lld\n",fa[0][u]);
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
7
1 6
1 7
7 3
3 2
7 5
5 4
4
1 2
1 4
1 6
2 6 7
*/