#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0 , f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;int a[maxn];
struct Segment_Tree{
    struct node{
        int sum0, sum1, lmx0, lmx1, rmx0,rmx1, mxx0,mxx1;
        int l, r, tag, revtag;

        node(int s0    ,int s1  ,int l0  ,int l1  ,int r0  ,int r1  ,int m0  ,int m1  ,int l,int r,int tag = -1,int revtag = 0
             ):sum0(s0),sum1(s1),lmx0(l0),lmx1(l1),rmx0(r0),rmx1(r1),mxx0(m0),mxx1(m1), l(l), r(r),tag(tag)    ,revtag(revtag){}
        
        node(int col = 0,int l = 0,int r = 0,int tag = -1,int revtag = 0):l(l),r(r),tag(tag),revtag(revtag){
            int x = r - l + 1;
            if(!col){sum0 = x;sum1 = 0;lmx0 = x;lmx1 = 0;rmx0 = x;rmx1 = 0;mxx0 = x;mxx1 = 0;}
            else    {sum0 = 0;sum1 = x;lmx0 = 0;lmx1 = x;rmx0 = 0;rmx1 = x;mxx0 = 0;mxx1 = x;}
        }
    }d[maxn << 2];
    node mergenode(node l,node r){
        return node(
            l.sum0 + r.sum0,l.sum1 + r.sum1,
            (l.r - l.l + 1 == l.sum0) ? (l.sum0 + r.lmx0) : l.lmx0,(l.r - l.l + 1 == l.sum1) ? (l.sum1 + r.lmx1) : l.lmx1,
            (r.r - r.l + 1 == r.sum0) ? (r.sum0 + l.rmx0) : r.rmx0,(r.r - r.l + 1 == r.sum1) ? (r.sum1 + l.rmx1) : r.rmx1,
            max(max(l.mxx0,r.mxx0),l.rmx0 + r.lmx0), max(max(l.mxx1,r.mxx1),l.rmx1 + r.lmx1),l.l,r.r
        );
    }
    void change(int p,int col){
        int x = d[p].r - d[p].l + 1;
        if(col < 2){d[p] = node(col,d[p].l,d[p].r,col);}
        else{
            swap(d[p].sum0,d[p].sum1); swap(d[p].lmx0,d[p].lmx1);
            swap(d[p].rmx0,d[p].rmx1); swap(d[p].mxx0,d[p].mxx1);
            d[p].revtag ^= 1;
        }
    }
    void pushdown(int p){
        if(d[p].tag != -1){change(p << 1,d[p].tag);change(p << 1 | 1,d[p].tag);}
        if(d[p].revtag){change(p << 1,2);change(p << 1 | 1,2);}
        d[p].tag = -1;d[p].revtag = 0;
    }

    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],l,l);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int col){
        if(s <= l && r <= t){change(p,col);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,col);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,col);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int s,int t,int col){update(1,n,s,t,1,col);}
    node query(int s,int t){return query(1,n,s,t,1);}
}tree;
signed main(){
    n = read(); m = read();for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(1,n,1);int opt, l ,r;
    for(int i = 1;i <= m;i++){
        opt = read(); l = read() + 1; r = read() + 1;
        if(opt <= 2)tree.update(l,r,opt);
        if(opt == 3)printf("%d\n",tree.query(l,r).sum1);
        if(opt == 4)printf("%d\n",tree.query(l,r).mxx1);
    }
    return 0;
}