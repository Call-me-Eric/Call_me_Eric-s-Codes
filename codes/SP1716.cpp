#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, m;
int a[maxn];

struct Segment_Tree{
    struct node{
        int lmax, rmax,maxx, sum;
        node(int sum = 0,int lmax = 0,int rmax = 0,int maxx = 0):sum(sum),lmax(lmax),rmax(rmax),maxx(maxx){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum,max(l.lmax,l.sum + r.lmax),
                        max(r.rmax,r.sum + l.rmax),max(max(l.maxx,r.maxx),l.rmax + r.lmax));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],a[l],a[l],a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd,upd,upd,upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1, upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    int query(int l,int r){return query(1,n,l,r,1).maxx;}
    void update(int pos,int upd){update(1,n,pos,1,upd);}
}tree;

signed main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    m = read(); tree.build(1,n,1); int opt, u, v;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();
        if(!opt){tree.update(u,v);}
        else printf("%lld\n",tree.query(u,v));
    }
    return 0;
}