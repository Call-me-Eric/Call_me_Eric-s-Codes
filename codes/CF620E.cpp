#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
int n, m, a[maxn], col[maxn];
vector<int> edg[maxn];

int dfn[maxn], idx, siz[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx;siz[u] = 1;
    for(int v : edg[u])if(v != f){dfs(v, u);siz[u] += siz[v];}
}

struct Segment_Tree{
    struct node{
        ll sum, tag; bool chg;
        node(ll sum = 0LL,ll tag = 0LL,bool chg = 0):sum(sum),tag(tag),chg(chg){}
    }d[maxn << 2];
    void pushdown(int p){
        if(d[p].chg){
            d[p << 1].chg = d[p << 1 | 1].chg = 1;
            d[p << 1].tag = d[p << 1].sum = d[p].tag;
            d[p << 1 | 1].tag = d[p << 1 | 1].sum = d[p].tag;
            d[p].chg = 0;
        }
    }
    node mergenode(node l,node r){return node(l.sum | r.sum);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(1LL << ((ll)col[l]));return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,ll upd){
        if(s <= l && r <= t){d[p] = node(upd,upd,1);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1, upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1| 1, upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;pushdown(p);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    ll query(int s,int t){return query(1,n,s,t,1).sum;}
    void update(int s,int t,ll upd){update(1,n,s,t,1,upd);}
    void build(){build(1,n,1);}
}tree;

int popcount(ll x){int cnt = 0;for(;x;x -= (x & (-x)))cnt++;return cnt;}

signed main(){
    n = read();m = read();int u, v, opt;
    for(int i = 1;i <= n;i++){a[i] = read();}
    for(int i = 1;i < n;i++){
        u = read(); v=  read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 0);for(int i = 1;i <= n;i++){col[dfn[i]] = a[i];}
    // printf("DEEEEEEEE:%lld",tree.d[1].sum);
    tree.build();
    for(int i = 1;i <= m;i++){
        opt = read();u = read();
        if(opt == 1){
            v = read(); ll x = v;
            tree.update(dfn[u],dfn[u] + siz[u] - 1,1LL << x);
            // printf("DEBUG:%lld %lld",1LL << x,tree.d[1].sum);
        }
        else{
            ll x = tree.query(dfn[u],dfn[u] + siz[u] - 1);
            // printf("DEBUG:%lld ; %lld\n",x,tree.d[1].sum);
            printf("%d\n",popcount(x));
        }
    }
    return 0;
}