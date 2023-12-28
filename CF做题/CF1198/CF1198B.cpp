#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, a[maxn], m;
struct Segment_Tree{
    struct node{
        int maxx, tag;
        node(int maxx = 0,int tag = 0):maxx(maxx),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].maxx = max(d[p].tag,d[p << 1].maxx);
            d[p << 1].tag = max(d[p].tag,d[p << 1].tag);
            d[p << 1 | 1].maxx = max(d[p].tag,d[p << 1 | 1].maxx);
            d[p << 1 | 1].tag = max(d[p].tag,d[p << 1 | 1].tag);
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd);return;}
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].tag = max(d[p].tag,upd);d[p].maxx = max(d[p].maxx,upd);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1, upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void query(int l,int r,int p){
        if(l == r){printf("%d ",d[p].maxx);return;}
        int mid = l + r >> 1;pushdown(p);
        query(l,mid,p << 1);query(mid + 1,r,p << 1 | 1);
    }
}tree;

signed main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(1,n,1);m = read();int u, opt;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read();
        if(opt == 1)tree.update(1,n,u,1,read());
        else tree.update(1,n,1,n,1,u);
    }
    tree.query(1,n,1);
    return 0;
}